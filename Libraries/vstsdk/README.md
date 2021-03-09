Get the Steinberg VST 2.4 SDK and copy it in the `Libraries/vstsdk` directory. The structure of the `Libraries/vstsdk` needs to be as follows:

```
Libraries/vstsdk/
├── pluginterfaces
│   └── vst2.x
│       ├── aeffect.h
│       ├── aeffectx.h
│       └── vstfxstore.h
├── aeffeditor.h
├── audioeffect.cpp
├── audioeffect.h
├── audioeffectx.cpp
├── audioeffectx.h
├── CMakeLists.txt
└── vstplugmain.cpp
```

Now create a directory `CMake` in the `Builds` directory and run `cmake ../.. && make`. Copy the resulting `open303.so` file to a place where your DAW can find it.

Thanks to the [Airwindows repository](https://github.com/airwindows/airwindows) for these instructions!
