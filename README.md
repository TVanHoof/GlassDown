# GlassDown

An audio effect plugin built with [JUCE](https://juce.com). GlassDown is a
barebones wave shapers, which applies a graph of segments to incoming
samples: the segment graph describes how the signal is shaped across the sample
range, and `PluginLogic` walks it.

The DSP lives in `src/PluginLogic`, which is deliberately free of any JUCE
dependency. It compiles on its own and is unit-tested without building a plugin,
which is why the test suite links only `PluginLogic` and googletest.

## Status

Early. The plugin builds as VST3, AU and Standalone; the segment logic is under
active development.

## Building

Requirements: CMake 3.25 or newer, a C++17 compiler, Ninja or Make, and the
platform development packages JUCE needs (listed per platform below). JUCE and
googletest are git submodules and must be initialised.

```sh
git clone --recurse-submodules https://github.com/TVanHoof/GlassDown.git
cd GlassDown
```

### Linux

```sh
sudo apt-get install ninja-build ccache \
  libasound2-dev libfreetype-dev libfontconfig1-dev \
  libx11-dev libxcomposite-dev libxcursor-dev libxext-dev \
  libxinerama-dev libxrandr-dev libxrender-dev libxi-dev \
  libglu1-mesa-dev mesa-common-dev libegl-dev

cmake --preset linux-release
cmake --build --preset linux-release
ctest --preset linux-release
```

### macOS

```sh
brew install ccache

cmake --preset macos-release
cmake --build --preset macos-release
ctest --preset macos-release
```

### Windows

```sh
cmake --preset windows-release
cmake --build --preset windows-release
ctest --preset windows-release
```

Artefacts are written to `build/<preset>/GlassDown_artefacts/Release/`, which
contains the `VST3` and `Standalone` bundles.

### Version numbers

`PLUGIN_VERSION` defaults to `0.0.0` and is numeric, at most four components:

```sh
cmake --preset linux-release -DPLUGIN_VERSION=1.2.3
```

Release builds take the version from the tag. Pushing `v1.2.3` builds all three
platforms with `-DPLUGIN_VERSION=1.2.3` and publishes a GitHub Release once
every job passes; a tag with a suffix such as `v1.2.3-rc1` builds as `1.2.3` and
is published as a prerelease.

## Continuous integration

`ci.yml` runs on every push and pull request, and covers Linux only. Windows and
macOS run when a `v*` tag is pushed, or on demand via *Run workflow*, where you
can pick the platforms and configurations.

## Licence

GlassDown is free software, licensed under the **GNU Affero General Public
License**, version 3 or later. See [LICENSE](LICENSE) for the full text.

You can run, study, modify and redistribute GlassDown, and you can charge for
it. If you distribute it — including a compiled VST3, AU or Standalone binary —
you must also offer the corresponding source under the same licence. That is the
one obligation the AGPL adds over the GPL, and it is why every release publishes
a source archive alongside the binaries.

Audio you render with GlassDown is not covered by the licence: the AGPL covers
the software, not its output.

GlassDown links against JUCE, which is dual licensed. GlassDown uses the AGPLv3
option; the JUCE commercial licence is not used and is not required. Third-party
components vendored by JUCE keep their own licences, listed in
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
