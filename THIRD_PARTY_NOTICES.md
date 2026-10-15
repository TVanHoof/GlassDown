# Third-party notices

GlassDown is licensed under the GNU Affero General Public License v3 or later;
see [LICENSE](LICENSE). This file lists the third-party components that the
JUCE submodule vendors, because their licences — unlike a commercial EULA —
require their notices to travel with the software. That is why they appear
here and in the source published with every release.

Generated from the SPDX bill of materials at `deps/JUCE/JUCE.spdx.json`, which
is maintained upstream by JUCE. Re-check it after a submodule bump.

## Vendored and used

| Component | Version | Licence |
| --- | --- | --- |
| AudioUnitSDK | 1.1.0 | Apache-2.0 |
| Box2D | 2.2.1 | Zlib |
| CHOC | 123d322c7ed4de8f0db2c30edea07b248dfe14c4 | ISC |
| FLAC | 1.5.0 | BSD-3-Clause |
| HarfBuzz | 14.2.1 | MIT-Modern-Variant |
| jpeglib | 10.0 | IJG |
| libogg | 1.3.6 | BSD-3-Clause |
| libopusenc | 0.3 | BSD-3-Clause |
| libpng | 1.6.58 | libpng-2.0 |
| libvorbis | 1.3.7 | BSD-3-Clause |
| libwebp | 1.6.0 | BSD-3-Clause |
| LunaSVG | 3.5.0 | MIT |
| OpenGL registry headers | 2024-01-16 | BSD-3-Clause AND MIT |
| Opus | 1.6.1 | BSD-3-Clause |
| opusfile | 0.12-59-g6dfd29e | BSD-3-Clause |
| PlutoVG | 1.3.2 | MIT |
| reaper-sdk | ec0c1dc1655eb6a192fa7a22c2258a38a5ebbe9c | Zlib |
| SheenBidi | 2.9.0 | Apache-2.0 |
| VST3 SDK | 3.8.0 | MIT |
| zlib | 1.3.2 | Zlib |

## Vendored but not part of the GlassDown build

Listed for completeness. None of these is compiled into the GlassDown binaries.

| Component | Version | Licence | Why not |
| --- | --- | --- | --- |
| AAX SDK | 2.9 | LicenseRef-Avid-AAX OR GPL-3.0-only | `FORMATS` is `VST3 AU Standalone`; AAX is Avid-proprietary or GPL-3.0-only, so it could not be combined with AGPLv3 in any case. |
| ASIO SDK | 2.3 | LicenseRef-Steinberg-ASIO OR GPL-3.0-only | Not targeted, and proprietary-or-GPL-3.0-only. |
| Box2D testbed | 2.2.1 | Zlib | Example application. |
| Chromium cubic_bezier | 3e1a26c44c024d97dc9a4c09bbc6a2365398ca2c | BSD-3-Clause | Browser helper only. |
| examples | 9.0.3 | ISC | JUCE's own examples, never built by GlassDown. |
| Gradle wrapper | 8.14.5 | Apache-2.0 | Android build support. |
| lilv | 0.24.12 | ISC | Vendored with LV2. |
| LV2 | 1.18.0 | ISC | `FORMATS` is `VST3 AU Standalone`. |
| Oboe | 1.10.0 | Apache-2.0 | Android audio. |
| Projucer icons | — | MIT | Projucer media, not compiled into the plugin. |
| pslextensions | — | LicenseRef-Public-Domain | Vendored with the JUCE examples. |
| QuickJS | 2021-03-27 | MIT | The generated module defines set `JUCE_WEB_BROWSER=0`. |
| serd | 0.30.10 | ISC | Vendored with LV2. |
| sord | 0.16.9 | ISC | Vendored with LV2. |
| sratom | 0.6.8 | ISC | Vendored with LV2. |

## JUCE

The 28 JUCE modules in this build are declared in the SBOM as
`AGPL-3.0-only OR LicenseRef-JUCE-Commercial`. GlassDown takes the AGPLv3
option, which is what makes GlassDown as a whole AGPL-3.0-or-later; JUCE
itself remains `AGPL-3.0-only`.

## Tests

[googletest](deps/googletest) is BSD-3-Clause and is used by the `PluginLogicTests`
target only. It is never linked into a distributed binary.

## Regenerating

```
jq -r '.packages[] | [.name, .versionInfo, .licenseDeclared] | @tsv' deps/JUCE/JUCE.spdx.json
```
