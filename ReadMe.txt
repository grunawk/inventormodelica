  Inventor Modelica Translator
  ============================
  
  This is based on the standard Inventor API translator example.

  Building and Installing
  =======================

  Choose Debug x64 or Optimize x64 configuration.

  Modify or delete the project's post-build step.

  The current post-build step convenient for Inventor developer builds in the R: drive:

  1) COPY "$(TargetDir)$(TargetFileName)" R:\lib\$(TargetedSDKConfiguration)_$(PlatformTarget);
  2) COPY "$(ProjectDir)Autodesk.TranslatorModelica.Inventor.addin" R:\lib\$(TargetedSDKConfiguration)_$(PlatformTarget)\addins

  For normal Inventor installations:

  1) COPY "$(TargetDir)$(TargetFileName)" C:\Program Files\Autodesk\Inventor 20XX\Bin
  2) COPY "$(ProjectDir)Autodesk.TranslatorModelica.Inventor.addin" C:\ProgramData\Autodesk\Inventor 20XX\Addins.

  Make sure to replace XX with appropriate year and update install path if different.

  You can also delete the post-build steps and do this manually, of course.

  No registration of the dll is necessary.


  Using the translator
  ====================

  1) Startup Inventor
  2) Open an assembly document
  3) Save Copy As... (under Save As...)
  4) Select the Modelica output format
  5) Select Options... if needed
  6) Save the .mo file

  Options
  =======

  [ ] Joints only
      If checked, do not convert assembly constraints into joints. Only translate
      joints. Joints were added to Inventor late in life. DOF can be defined by
      collections of more atomic constraints (mate, flush, angle). By default,
      the translator interprets constraints that leave DOF as a joint if possible.
      Some DOF does not map to the basic Modelica multi-body joint types.

      If the Inventor model has "top down" created parts, they will often be constrained
      to a workplane by default. This can result in constraint redundancy which will cause
      Modelica simulation to fail. You can simply delete the planar joints in the Modelica
      editor, or check "Joints only" to ignore the planar constraints.

  [ ] Remove massless ungrounded bodies


  Constraint and DOF Reduction

  These options belong to the undocumented API method to extract rigid groups and joints
  from Inventor's assembly constraint solver. Some of these options need more
  investigation.

  [X] Remove rotations about mass center

      This will remove rotational DOF between a bolt and a hole. Often, there is
      unnecessary DOF left in the model when things like bolts are added using the "insert"
      constraint. The bolt's rotation is about inertia axis at center of gravity.

  [ ] Remove rotations about bounding box center

      Like above but uses the rotating part's bounding box center/axes,
      instead of mass properties.

  [X] Reduce redundant constraints

      TODO: find example of what this does. Certainly, not all redundancies
      are removed when this is checked.

  [X] Look for double-bearing joints

      TODO: find example of what this does. My guess is that a complex double-bearing
      rotation is converted to a simpler revolute joint -- but not sure.

  [ ] Merge large mass differentials

      If checked, "Difference" value is used to find relatively small/light bodies that
      can be merged into larger/heavier bodies to which they are constrained.

  Gravity

  Default: uniform earth gravity in -Y.

  Turn off gravity or select a different axis from world XYZ.

 