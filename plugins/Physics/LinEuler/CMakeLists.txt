# coolfluid_physics_lineuler

list( APPEND coolfluid_physics_lineuler_files
  LibLinEuler.cpp
  LibLinEuler.hpp
  LinEuler2D.cpp
  LinEuler2D.hpp
  Cons2D.hpp
  Cons2D.cpp
)

list( APPEND coolfluid_physics_lineuler_cflibs coolfluid_physics )

coolfluid_add_library( coolfluid_physics_lineuler )

