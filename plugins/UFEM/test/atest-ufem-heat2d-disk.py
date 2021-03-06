import sys
import coolfluid as cf

# Global configuration
cf.Core.environment().options().configure_option('log_level', 4)

# setup a model
model = cf.Core.root().create_component('HotModel', 'cf3.solver.Model')
model.setup(solver_builder = 'cf3.UFEM.HeatConductionSteady', physics_builder = 'cf3.physics.DynamicModel')
solver = model.get_child('HeatConductionSteady')
domain = model.get_child('Domain')

# load the mesh (passed as first argument to the script)
domain.load_mesh(file = cf.URI(sys.argv[1]), name = 'Mesh')

# lss setup
lss = model.create_component('LSS', 'cf3.math.LSS.System')
lss.options().configure_option('solver', 'Trilinos');
solver.options().configure_option('lss', lss)
lss.get_child('Matrix').options().configure_option('settings_file', sys.argv[2]);

# Boundary conditions
bc = solver.get_child('BoundaryConditions')
bc.add_constant_bc(region_name = 'inner', variable_name = 'Temperature').options().configure_option('value', 10)
bc.add_constant_bc(region_name = 'outer', variable_name = 'Temperature').options().configure_option('value', 35)

# run the simulation
model.simulate()

# Write result
domain.write_mesh(cf.URI('atest-ufem-heat2d-disk.pvtu'))
