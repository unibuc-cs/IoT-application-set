# How to build Docker images for multi-arch

Inside `utils` there are two scripts `./build_docker_images_for_arch.sh` and `./create_tag_for_multi_arch.sh`.

 1. Login into Docker Hub using `docker login`.
 2. Change `USERNAME, PLATFORM, TAG` from `build_docker_images_for_arch` accordingly.
 3. Run `build_docker_images_for_arch`.
 4. This will upload the images on Docker hub under the tag that you chose.
 5. To create a unique tag for all the architectures use `create_tag_for_multi_arch.sh`. Change `USERNAME` accordingly. 

## References

The following tutorials were very helpful":

 - [Leverage multi-CPU architecture support](https://docs.docker.com/desktop/multi-arch/) - How to build images for different architectures with `docker buildx`
 - [Multi-architecture images in your Azure container registry](https://docs.microsoft.com/en-us/azure/container-registry/push-multi-architecture-images) - How to build multi-arch images with the same tag (usually "latest")
