cacamera = Components.create_entity()
Components.add_transform(camera)
Components.add_camera(camera)
camera.camera.main = true;
camera.camera:set_perspective(1.0471975512, 4/3, 0.1, 100)

camera.transform.position.z = 10

cube = Components.create_entity()
Components.add_transform(cube)
Components.add_renderable(cube)
cube.renderable.shader_program = Resources.load_shader("default", "Shaders/vert_shader.glsl", "Shaders/frag_shader.glsl")
cube.renderable.textures[1] = Resources.load_texture("awesomeface.png")
cube.renderable.mesh = Resources.cube

light = Components.create_entity()
Components.add_transform(light)
Components.add_directional_light(light)
light.directional_light.direction = Vec3.new(1,1,-1):normalized()
light.directional_light.color = Vec3.new(1,1,1)
light.directional_light.intensity = 0.5