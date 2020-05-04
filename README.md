# Ray Tracing 

This is my Capstone project for the C++ Nanodegree program by Udacity. 

## Description 
Ray tracing is a method used in 3D graphics rendering to realistically project three-dimensional objects into a two-dimensional image. In this application, the user can specify the positions and sizes of objects in the real world, which will then be rendered as an image. 

This basic implementation renders spheres, but is flexible enough to handle more complicated object shapes as well. A good reference for the overall concept is [Scratchapixel 2.0](scratchapixel.com). 

## Code Structure 

This project is divided into the following sub-directories:
```
├── configs (JSON file for configuration information)
│   ├── config.json 
├── external
│   ├── nlohmann (For JSON file parsing)
│   ├── png++-0.2.9 (To save outputs as .png files)
│   ├── spdlog (To log intermediate outputs for debugging)
│   ├── argparse.h (To parse command line arguments)
├── include 
│   ├── image_options.h (Image height, width, etc.)
│   ├── image_saver.h (Handles saving image to file)
│   ├── json_reader.h (Reading and parsing JSON file)
│   ├── ray.h (Generic ray object - origin and direction)
│   ├── sphere.h (Generic sphere object)
│   ├── vector3d.h (Generic vector - handles vector math)
├── results (Store output images here)
│   ├── out.png
├── src
│   ├── image_options.cpp 
│   ├── image_saver.cpp 
│   ├── json_reader.cpp 
│   ├── main.cpp 
│   ├── ray.cpp
│   ├── sphere.cpp
│   ├── vector3d.cpp
├── CMakeLists.txt
├── README.md
├── .clang-format
└── .gitignore
```

### Program flow 

The core of the program is the `render_image()` function in [main.cpp](src/main.cpp), where each pixel of the image is iterated through. For each pixel, a ray is projected into space. A `Ray` object has two `Vector3D` objects, corresponding to the origin and direction of the ray. 

Each ray is tested for intersection with all the objects in the scene. This is done in the `Sphere::intersects()` method. The objects in the scene can either be randomly generated or specified in the [configuration JSON file](configs/config.json).

The color of the sphere closest to the origin in the direction of the ray is stored as the pixel value. This value is obtained from `Sphere::getSurfaceProperties()`. 

After iterating over all the pixels, the image will be fully formed and ready to be saved. It is passed to the `ImageSaver` object to save to file. The filename is specified in the [configuration JSON file](configs/config.json).

## Dependencies for Running Locally

- cmake >= 3.7
- make >= 4.1 (Linux)
- gcc/g++ >= 5.4

This has only been tested on Linux, but comparable versions on other operating systems should work just as well. 

## External libraries 

This source code uses the following libraries. These are header-only libraries, so no additional dependencies are required. 
- [JSON for Modern C++](https://github.com/nlohmann/json)
    - This was used to parse the configuration JSON file and create objects using the configuration data. ([JSONReader](src/json_reader.cpp))
- [png++](https://www.nongnu.org/pngpp/doc/0.2.9/)
    - This library was used to write the image data to a .png file. ([ImageSaver](src/image_saver.cpp))
- [spdlog](https://github.com/gabime/spdlog/)
    - This is a fast logging library. I used this to avoid printing debug information to the console. 
- [argparse](https://github.com/jamolnng/argparse)
    - Library to parse command line arguments. ([main.cpp](src/main.cpp))

## Running instructions 

To build this project, first create a build directory in the top-level directory. 
```bash
mkdir build 
cd build
```
Then compile the program. 
```bash
cmake .. && make
```
Run the executable. 
```bash
./raytracing 
```
There are a few command line options that can be used as well. 
```bash 
Usage: raytracing [options...]
Options:
    -d, --debug            Enable debug mode      
    -r, --random           Use random spheres     
    -h, --help             Shows this page 
```

## Sample outputs

Here are some examples of the renderings this program generates: 

Object positions specified manually in [config file](configs/config.json):

![alt text][demo_output]

[demo_output]: results/out_demo.png "Manually specified object positions"

Objects generated at random: 

![alt text][random_output]

[random_output]: results/out_random.png "Random spheres"
## Rubric Requirements

### Loops, Functions, I/O

| Criteria  | Location |
|-----------------------------------------------------------------------------------------------|----------------------------------|
| The project demonstrates an understanding of C++ functions and control structures.             | All files                        |
| The project reads data from a file and process the data, or the program writes data to a file. | [JSONReader](src/json_reader.cpp), [ImageSaver](image_saver.cpp) |

### Object Oriented Programming

| Criteria  | Location |
|-----------------------------------------------------------------------------------------------|----------------------------------|
| The project uses Object Oriented Programming techniques.           | All files                        |
| Classes use appropriate access specifiers for class members. | All files |
|Class constructors utilize member initialization lists. | [ImageOptions](src/image_options.cpp), [ImageSaver](src/image_saver.cpp), [Ray](ray.cpp), [Sphere](sphere.cpp), [Vector3D](src/vector3d.cpp)| 
|Classes encapsulate behavior. | All files | 
| Overloaded functions allow the same function to operate on different parameters. | [Sphere](sphere.cpp), [Vector3D](src/vector3d.cpp) | 
| Templates generalize functions in the project. | [Ray](ray.cpp), [Sphere](sphere.cpp), [Vector3D](src/vector3d.cpp) | 

### Memory Management
| Criteria  | Location |
|-----------------------------------------------------------------------------------------------|----------------------------------|
| The project makes use of references in function declarations.           | All files                        |
| The project uses destructors appropriately. | [ImageSaver](src/image_saver.cpp), [JSONReader](src/json_reader.cpp) | 
| The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. | [ImageSaver](src/image_saver.cpp), [JSONReader](src/json_reader.cpp) | 
| The project uses move semantics to move data, instead of copying it, where possible. | [Main function](main.cpp) | 
| The project uses smart pointers instead of raw pointers. | [Main function](main.cpp) | 
