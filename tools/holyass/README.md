# holyass

## Notes

* The model armature cannot be named "armature", yeah, I know.
* bones and meshes CANNOT share names
* If using IK or fancy animation features make sure to enable sampling on export, or otherwise bake it to real bones.

## Blender glTF Export Settings

Default: unselected unless listed below

* Format: glTF Separate
* Keep original
* Transform
  * +Y Up
* Data
  * Mesh
    * Apply Modifies
    * UVs
    * Normals
    * Tangents
  * Vertex Colors: None
* Material
  * Materials: Export
  * Images: Automatic
  * *NOTE: holyass gets uses the texture filenames, that's all. The actual exported image unused*
* Skinning
  * Bone Influence: 4
* Animations
  * Animation mode: NLA Tracks
  * *OPTIONAL: Sampling*
  * Optimize Animations
    * Optimize Animations
    * Force keeping channels for bones

## Blender Animation Ordering

I use NLA Tracks to organize animations. The order of the NLA tracks as shown in the *View Layer* tree. Reordering these tracks involves changing the order in the *NLA Editor*, but this does not necessarily reflect the ordering in the *View Layer*. It's weird, I know. Blame Blender.

## License

[MIT+NIGGER](https://plusnigger.autism.exposed/)
