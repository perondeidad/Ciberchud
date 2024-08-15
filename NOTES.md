# TODO

* can we backface cull earlier?
* visflag culling regular models
* animation transition/blending
* levels
* mobs
* weapons
* clip triangles against side planes to try to avoid frag distance == 0 issues
* flags for TOS
* specular highlight is fucked for BSP surfaces not aligned to worldspace
  * probably need to implement SURF_PLANEBACK, actually no, didn't help
  * check out fteqw defaultwall.glsl using tvec/svec dot * eyevector
  * see ltface.c for tvec/svec calc
* because `light_dynamic` starts with `light`, ericw-tools bakes with it. Probably rename `light_dynamic` to something else to avoid this

# Bugs

* shader.c:146: get_lightmap_value_interp: Assertion `uv.x <= 1.0' failed.`
* triangle line artifacts in shadow map
* some type of race condition in starting TempleOS
  * looks like a race condition related to realloc/malloc
  * it's fixed when I stop mallocing, or I calloc instead of malloc
  * playing sound seems to resolve the issue, related to audio thread?
* Chromium browsers (Linux only?) have bad performance on first page load, refreshing fixes. Doesn't seem to affect unoptimized builds.
* wireframe of clipped models is weird
* maybe create bsp model based off of a global vischeck or something to more gracefully handle invisible brushes
* `__builtin_ceilf` in combination with LTO causes infinite loop
* door has bad visleafs?
* doors have bad clipnodes?
* luxmap is wrong if texture is world-aligned and not object-aligned
* BUG REPORT: user gets extremely choppy gameplay while very high framerate (>200 FPS), sometimes becoming Inf and locking. Possibly related to fixed time step of the world update. (platform: TOS)
* investigate norm sqrtf in ubershader

# Ideas

* Deferred Shading
* GoldSrc style decals https://github.com/FWGS/xash3d-fwgs/blob/master/ref/gl/gl_decals.c

# Shader Ideas

* https://www.shadertoy.com/user/rasmuskaae
* https://www.shadertoy.com/view/3lGBzW
* https://www.shadertoy.com/view/4sX3RM
* https://www.shadertoy.com/view/4slXWn
* https://www.shadertoy.com/view/XdSGzR
* https://www.shadertoy.com/view/XdXGRM
* https://www.shadertoy.com/view/Xdc3RX
* https://www.shadertoy.com/view/flSBR3
* https://www.shadertoy.com/view/ldscWH
* https://www.shadertoy.com/view/lsX3WM

# Texture Resizing

Lanczos3 preserves details better than other tested resizing algos

# Notes

* cglm modified with const parameters where needed to fix warnings

# Making Grayscale Textures

* Convert to grayscale
* Use GIMP's "Brightness & Contrast" to increase contrast
* Save as 8bit grayscale

# Scaling Normal Maps

* Use Krita's Normalization filter after scaling to ensure values are properly normalized
* Don't forget to save as 8bit RGB with sRGB builtin profile, use exiftool to strip ICC profile and other crap Krita inserts

# Editing the WAD

* I use Wally (via wine)
* Scaling the texture in the WAD is effectively UV scaling. I'll typically scale a 512px to 256px, it depends on the level of detail required.

# Neato Burrito Models (maybe to use later)

* Andrei Milin: https://sketchfab.com/3d-models/lazer-gun-aep-9-4603956c1f824e49a1ffe8c6263317cd (CC BY 4.0)
* Andrei Milin: https://sketchfab.com/3d-models/revolver-rs-baikal-9ce9af8811c345ba8da22c931c73e53b (CC BY 4.0)
* Andrei Milin: https://sketchfab.com/3d-models/sci-fi-pistol-fab28aeb14894752b49149ef00926aff (CC BY 4.0)
* https://sketchfab.com/3d-models/9-mm-5124e7fe60fb4d3ab62460609d23f365
* https://sketchfab.com/3d-models/racecar-lowpoly-45840e2136c44080b4c1e7521cce8db3
* https://sketchfab.com/3d-models/shotgun-shells-1807bebe90c64dbaaf60d6de50eb0a3d
* NksXxX: https://sketchfab.com/3d-models/gun-8530f957dae0409bbbaa4ffea0bd7efe (CC BY 4.0)
