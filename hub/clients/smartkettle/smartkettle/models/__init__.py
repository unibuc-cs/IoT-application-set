# flake8: noqa

# import all models into this package
# if you have many models here with many references from one model to another this may
# raise a RecursionError
# to avoid this, import only the models that you directly need like:
# from from smartkettle.model.pet import Pet
# or import this package, but before doing it, use:
# import sys
# sys.setrecursionlimit(n)

from smartkettle.model.inline_object import InlineObject
from smartkettle.model.inline_object1 import InlineObject1
from smartkettle.model.inline_response200 import InlineResponse200
from smartkettle.model.inline_response2001 import InlineResponse2001
from smartkettle.model.inline_response2002 import InlineResponse2002
from smartkettle.model.inline_response2003 import InlineResponse2003
from smartkettle.model.inline_response2004 import InlineResponse2004
from smartkettle.model.make_tea_temperature import MakeTeaTemperature
