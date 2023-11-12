# Vulkan

- [vulkan](https://www.vulkan.org/)
  - [learn](https://www.vulkan.org/learn)
  - [guide](https://docs.vulkan.org/guide/latest/index.html)
  - [tutorial](https://docs.vulkan.org/tutorial/latest/index.html)
  - [samples](https://docs.vulkan.org/samples/latest/README.html)

## SDK

- lunarg: [getting started](https://vulkan.lunarg.com/doc/sdk/latest/linux/getting_started_ubuntu.html)

### Ubuntu 22.04 (Jammy Jellyfish)

```bash
wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list https://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
sudo apt update
```

```bash
sudo apt install vulkan-sdk
sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools
sudo apt install libglfw3-dev libglm-dev
sudo apt install libxxf86vm-dev libxi-dev
```

#### Shader Compiler

- google: [shaderc](https://github.com/google/shaderc/blob/main/downloads.md)

#### Verify Installation

```bash
vkvia
vulkaninfo
vkcube
```

## Links

- ~book: [Vulkan Programming Guide](https://www.vulkanprogrammingguide.com/)~
- github: [vinjn/awesome-vulkan](https://github.com/vinjn/awesome-vulkan)
- github: [SaschaWillems/Vulkan](https://github.com/SaschaWillems/Vulkan)
- github: [jherico/Vulkan](https://github.com/jherico/Vulkan)
- github: [waitin2010/awesome-computer-graphics](https://github.com/waitin2010/awesome-computer-graphics)
- github: [luisnts/awesome-computer-graphics](https://github.com/luisnts/awesome-computer-graphics)
- blog: [Computer Graphics Resouces](https://legends2k.github.io/note/cg_resources/)
- medium: [Resources for Beginning Graphics Programming](https://medium.com/vrtigo/resources-for-beginning-graphics-programming-c0da724381bc)
- blog: [How to Learn Computer Graphics: Explore the Best Online Courses and Resources](https://careerkarma.com/blog/computer-graphics/)
- blog: [Curated list of awesome lists](https://project-awesome.org/terkelg/awesome-creative-coding)
- [siggraph](https://education.siggraph.org/)
- [Real-Time Rendering Portal](https://www.realtimerendering.com/portal.html)
- [Fun With Graphics](https://www.opensourceagenda.com/projects/fun-with-graphics)

