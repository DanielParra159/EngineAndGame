# EngineAndGame

Before running game project it's necessary to set Working Directory "../../out/win32/". This has been developed with VS 2015.

It is a small game engine for creating games in C ++ with academic intentions. It has the following features:

# Render:
- Developed with SDL and OpenGL 3.
- Ability to render models by passing the vertices or file name.
- Changes in texture and color of the material.
- Render sprites and animated sprited with state machine.

# Audio:
- Developed with FMOD.
- Play (loop or normal), pause and volume control for 2D and 3D sounds.
- Management of audio listener.
- Separate sound effects and music manager.

# Scripting:
- Developed with LUA y LUABIND.
- Load and execute scripts.
- Publish C ++ functions and objects to be called from scripts.
- Access to variables in scripts.

# Input:
- Developed with SDL.
- Define actions and associate them with inputs, currently only keyboard and mouse.

# Physics:
- Developed with PhysX.
- Creation of BoxCollider(static, dynamic, kinematic).
- Creation of CapsuleController.
- Triggers and collisions notification.

# GameObjects:
- Use a component structure.
- A GameObject can have multiple components (currently only 1 of each type).

# Core:
- Management of game states (currently there cannot be 2 or more running).

# Demos:
- Snake Game 2D (in early versions of the engine).
- Snake Game in 3D (in early versions of the engine).
- 3D platform game with charger map from LUA and lights (developing).

You can find a compiled version in the"Build" folder.
Use arrows to move, space to jump, left control to attack, Q to shoot and esc to exit.

