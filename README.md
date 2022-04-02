# Open303

Open303 is a free and open source emulation of the famous Roland TB-303 bass synthesizer for the VST plugin interface (VST is a trademark of Steinberg Media Technologies GmbH). 

## Installation
### Linux
Get an older version of the [VST 3 Audio Plug-Ins SDK](https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/vstsdk3610_11_06_2018_build_37.zip) that includes the complete VST 2 SDK and extract it. Copy the files from `VST_SDK/vst2sdk/public.sdk/source/vst2.x/` and `VST_SDK/VST2_SDK/pluginterfaces` into `Libraries/vstsdk`. The structure of the `Libraries/vstsdk` directory needs to be as follows:

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

Now create a directory `CMake` in the `Build` directory in the root of the project, `cd` into that directory and run `cmake ../.. && make`. Copy the resulting `open303.so` file to a place where your DAW can find it, generally that would be `~/.local/lib/lxvst/`.

```
cd /path/to/open303/Libraries/vstsdk
curl -O "https://web.archive.org/web/20181016150224/https://download.steinberg.net/sdk_downloads/vstsdk3610_11_06_2018_build_37.zip"
unzip vstsdk3610_11_06_2018_build_37.zip
cp VST_SDK/VST2_SDK/public.sdk/source/vst2.x/* ./
cp -a VST_SDK/VST2_SDK/pluginterfaces ./
cd /path/to/open303
mkdir Build/CMake
cd Build/CMake
cmake ../.. && make
cp open303.so ~/.local/lib/lxvst/
```

Thanks to the [Airwindows repository](https://github.com/airwindows/airwindows) for these instructions!

### The Rest
#### Microsoft Visual Studio 2008
Load the solution-file Open303.sln (in the folder 'Build/VisualStudio2008') with Microsoft Visual Studio 2008 and try to build the plugin. If it works, you will find the results of the compilation (the final .dll and some intermediate files) in the subfolder 'Debug' or 'Release' of 'Build/VisualStudio2008', depending on whether you selected a debug- or release-build. 

#### CodeBlocks
Load the CodeBlocks project file Open303.cbp (in the folder 'Build/CodeBlocks') - and build away. The results will be found in the subfolder bin/Debug or bin/Release. On my setup, i get 15 compiler warnings which are all rooted in source files of the VST-SDK (not the Open303 code itself) - so i guess we may safely ignore them.