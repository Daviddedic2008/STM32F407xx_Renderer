import trimesh
import numpy as np
import math

def read_3mf_smooth_normals(filename):
    """
    Reads a 3MF file and returns flattened vertices and calculated
    smooth normals that correspond to the flattened vertex list.
    """
    # trimesh handles the 3MF file complexity internally
    mesh = trimesh.load_mesh(filename)

    # If the file contains multiple objects, merge them into a single mesh
    if isinstance(mesh, trimesh.Scene):
        mesh = mesh.dump(merge_primitives=True)

    vertices_unique = mesh.vertices
    normals_smooth = mesh.vertex_normals
    vertices_flat = vertices_unique[mesh.faces].reshape(-1, 3)
    normals_flat = normals_smooth[mesh.faces].reshape(-1, 3)
    
    return vertices_flat, normals_flat

def write_c_model_file(filename_3mf, output_c_file="model_output.c"):
    vertices, normals = read_3mf_smooth_normals(filename_3mf)
    num_triangles = len(vertices) // 3
    
    with open(output_c_file, 'w') as f:
        f.write("/**\n")
        f.write(" * Auto-generated C file from 3MF model data.\n")
        f.write(" * File: {}\n".format(filename_3mf.split('\\')[-1]))
        f.write(" */\n\n")
        f.write("#include \"screenDriver.h\"\n\n")

        # Assuming 'vec3' and 'triangle' structs are defined in screenDriver.h
        f.write("void loadModel(uint16_t color) {\n")
        f.write("    triangle t;\n")
        f.write("    t.color = color;\n")
        f.write("    t.raytracedStrength = 0; // Default to 0 as requested\n\n")

        # Iterate every 3 vertices to define a triangle
        for i in range(0, len(vertices), 3):
            # Vertices
            v1 = vertices[i]
            v2 = vertices[i+1]
            v3 = vertices[i+2]
            # Normals (all three are the same smooth normal we calculated for this face)
            n = normals[i]

            f.write("    // Triangle {}\n".format(i // 3))
            # Assigning to the correct struct member names (p1, p2, p3, normal)
            f.write("    t.p1.x = {}f; t.p1.y = {}f; t.p1.z = {}f;\n".format(v1[0], v1[1], v1[2]))
            f.write("    t.p2.x = {}f; t.p2.y = {}f; t.p2.z = {}f;\n".format(v2[0], v2[1], v2[2]))
            f.write("    t.p3.x = {}f; t.p3.y = {}f; t.p3.z = {}f;\n".format(v3[0], v3[1], v3[2]))
            f.write("    t.normal.x = {}f; t.normal.y = {}f; t.normal.z = {}f;\n".format(n[0], n[1], n[2]))
            f.write("    addTriangle(t);\n\n")

        f.write("}\n")
    
    print(f"Successfully wrote {num_triangles} triangles to {output_c_file}")

# --- Example Usage ---
# Replace 'your_file.3mf' with the path to your actual 3MF file
filename = "C:\\Users\\david\\Downloads\\models_stl\\PolySphere_Dodecahedron.3mf"
write_c_model_file(filename, "model_output.c")
