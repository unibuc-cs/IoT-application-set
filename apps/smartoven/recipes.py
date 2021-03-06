from flask import Blueprint, request, jsonify
from bson.objectid import ObjectId
from bson.errors import InvalidId
from db import get_db
from pymongo.errors import DuplicateKeyError


bp = Blueprint('recipes', __name__, url_prefix='/recipe')


def validate_recipe_body(body):
    if all([body.get('name'), body.get('prep_time'), body.get('prep_details'), body.get('baking_temperature')]):
        return True
    return False


def validate_recipe_for_update(body):
    if len(body) > 4:
        return False
    allowed_keys = ['name', 'prep_time', 'prep_details', 'baking_temperature']
    for key in body.keys():
        if key not in allowed_keys:
            return False
    return True


def get_recipes():
    db = get_db()
    recipes = db.recipes
    all_recipes = recipes.find({}, {'_id': 0})
    return list(all_recipes)


def get_one_recipe(name):
    if ' ' in name:
        name = name.replace(' ', '-')

    db = get_db()
    recipes = db.recipes
    recipe = recipes.find_one({'name': name})
    if recipe is not None:
        recipe['id'] = str(recipe['_id'] )
        recipe.pop('_id', None)
    return recipe


@bp.route('', methods=['GET'])
def get_all_recipes():
    """
    Get all recipes that are saved in the oven's database
    ---
    responses:
        200:
            description: Successfully returned a list of recipes
            content:
                application/json:
                    schema:
                        type: array
                        items:
                            type: object
                            required:
                                - name
                            properties:
                                name:
                                    type: string
                                prep_time:
                                    type: integer
                                prep_details:
                                    type: string
                                baking_temperature:
                                    type: integer
    """
    return jsonify(get_recipes())


@bp.route('', methods=['POST'])
def create_recipe():
    """
    Add a new recipe in the oven's database
    ---
    requestBody:
        required: true
        content:
            application/json:
                schema:
                    type: object
                    required:
                        - name
                        - prep_time
                        - prep_details
                        - baking_temperature
                    properties:
                        name:
                            type: string
                            example: Test recipe
                        prep_time:
                            type: integer
                            example: 10
                        prep_details:
                            type: string
                            example: Test recipe details
                        baking_temperature:
                            type: integer
                            example: 20
    responses:
        200:
            description: Successfully added a new recipe
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Successfully added the recipe
                            id:
                                type: string
                                example: 1
        400:
            description: Bad request - Missing required fields for a recipe
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Missing fields to perform adding of a recip
        409:
            description: Conflict - Duplicate recipe
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: A recipe with the same name already exists
    """
    body = request.json
    if body is None or not validate_recipe_body(body):
        return jsonify({ 'message': 'Missing fields to perform adding of a recipe' }), 400

    # Check if exists a recipe with this name
    try:
        new_recipe_id = add_recipe(body['name'], body['prep_time'], body['prep_details'], body['baking_temperature'])
    except DuplicateKeyError:
        return jsonify({ 'message': 'A recipe with the same name already exists' }), 409
    
    return jsonify({'message': 'Successfully added the recipe', 'id': str(new_recipe_id)})


@bp.route('/<recipe_name>', methods=['GET'])
def get_recipe(recipe_name=None):
    """
    Get recipe with the specified name from oven's database
    ---
    parameters:
        - name: recipe_name
          in: path
          required: true
          schema:
              type: string
    responses:
        200:
            description: Successfully returned the specified recipe
            content:
                application/json:
                    schema:
                        type: object
                        required:
                            - name
                        properties:
                            id: 
                                type: string
                            name:
                                type: string
                            prep_time:
                                type: integer
                            prep_details:
                                type: string
                            baking_temperature:
                                type: integer
        400:
            description: Bad request - Missing recipe name
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Invalid request
        404:
            description: Recipe not found
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Recipe not found
    """
    if recipe_name is None:
        return jsonify({ "message": "Invalid request" }), 400

    my_recipe = get_one_recipe(recipe_name)
    if my_recipe is None:
        return jsonify({"message": f"No {recipe_name} recipe"}), 404
    return my_recipe, 200


@bp.route('/<recipe_id>', methods=['PUT'])
def update_recipe(recipe_id=None):
    """
    Update a recipe with the specified id from oven's database
    ---
    parameters:
        - name: recipe_id
          in: path
          required: true
          schema:
              type: string
    requestBody:
        required: true
        content:
            application/json:
                schema:
                    type: object
                    properties:
                        name:
                            type: string
                        prep_time:
                            type: integer
                        prep_details:
                            type: string
                        baking_temperature:
                            type: integer
    responses:
        200:
            description: Successfully returned the specified recipe
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Successfully updated recipe with specified id
        400:            
            description: Bad request - Recipe is missing or has unallowed fields
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Request content contains unallowed fields
                                    
        404:
            description: Recipe not found
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: A recipe with the specified id does not exist
        500:
            description: Server error during recipe update
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: An error occured during update of the recipe
    """
    db = get_db()
    recipes = db.recipes
    updated_recipe = request.json
    if updated_recipe is None:
        return jsonify({ 'message': 'Request content is missing' }), 400
    if not validate_recipe_for_update(updated_recipe):
        return jsonify({ 'message': 'Request content contains unallowed fields' }), 400
    try:
        result = recipes.update_one({'_id': ObjectId(recipe_id)}, {"$set": updated_recipe})
        if result.matched_count == 0:
            return jsonify({ "message": "A recipe with the specified id does not exist" }), 404
        if result.modified_count == 0:
            return jsonify({ "message": "An error occured during update of the recipe" }), 500
    except InvalidId:
        return jsonify({ "message": "A recipe with the specified id does not exist"}), 404
    return jsonify({"message": f"Updated recipe with id {recipe_id}"})


def add_recipe(recipe_name, time, details, temperature):
    db = get_db()
    recipes = db.recipes
    recipe_name = recipe_name.replace(" ", "-")
    if time == 0:
        time = 30
    if temperature == 0:
        temperature = 150
    recipe = {'name': recipe_name, 'prep_time': time, 'prep_details': details, 'baking_temperature': temperature}
    result = recipes.insert_one(recipe)
    return result.inserted_id


@bp.route('/<recipe_id>', methods=['DELETE'])
def delete_recipe(recipe_id=None):
    """
    Delete a recipe with the specified id from oven's database
    ---
    parameters:
        - name: recipe_id
          in: path
          required: true
          schema:
              type: string
    responses:
        200:
            description: Successfully returned the specified recipe
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: Successfully deleted recipe with specified id
        404:
            description: Recipe not found
            content:
                application/json:
                    schema:
                        type: object
                        properties:
                            message:
                                type: string
                                example: A recipe with the specified id does not exist
    """
    db = get_db()
    recipes = db.recipes
    try:
        result = recipes.delete_one({'_id': ObjectId(recipe_id)})
        if result.deleted_count == 0:
            return jsonify({ "message": "A recipe with the specified id does not exist"}), 404
    except InvalidId:
            return jsonify({ "message": "A recipe with the specified id does not exist"}), 404

    return jsonify({"message": f"Deleted recipe with id {recipe_id}"}), 200
    
