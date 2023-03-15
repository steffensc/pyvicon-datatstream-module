from pyvicon_datastream import tools
import math
import numpy as np
import sys
import time


###### HELPER METHODS ######
def get_3d_dist_between_points(pos1, pos2):
    pos1_x, pos1_y, pos1_z = pos1[0], pos1[1], pos1[2]
    pos2_x, pos2_y, pos2_z = pos2[0], pos2[1], pos2[2]

    x = (pos1_x - pos2_x)**2
    y = (pos1_y - pos2_y)**2
    z = (pos1_z - pos2_z)**2
    dist_3D = math.sqrt(x + y + z)

    return dist_3D

def get_xyz_position(tracker_inst, obj_name):
    latency, frameno, position = tracker_inst.get_position(obj_name)
    if position != []:
        xyz_position = position[0][2:5] # get x,y,z only
        return xyz_position
    return []

def get_xyz_position_orientation(tracker_inst, obj_name):
    latency, frameno, position = tracker_inst.get_position(obj_name)
    if position != []:
        xyz_position = position[0][2:5] # get x,y,z only
        orientation = position[0][7] # get rotation around z axis
        return xyz_position, orientation
    return []

def get_static_position(tracker_inst, obj_name, collect_frame_no):
    valid_positions = []
    frames, skips = 0, 0
    while frames < collect_frame_no:
        xyz_position = get_xyz_position(tracker_inst, obj_name)
        if xyz_position != []:
            valid_positions.append(xyz_position)
            frames += 1
        else:
            skips += 1

        if skips > collect_frame_no:
            print(f"Too many Frames Skipped (>{skips})")
            return None

    # Calculate Median
    valid_positions = np.asarray(valid_positions)
    return  np.median(valid_positions, axis=0)

def round_list(list, digits):
    return [ round(elem, digits) for elem in list ]
############################



VICON_IP = "10.0.108.3"
OBJECT_NAME = "Imetron_oc"

# Intialize
print("Connecting to Vicon Tracker…")
vicontracker = tools.ObjectTracker(VICON_IP)

# Get initial start position by collecting a number of frames and calculate median
static_start_position = get_static_position(vicontracker, OBJECT_NAME, 50)
if static_start_position is not None:
    print(f"Static Start Position ({OBJECT_NAME}) XYZ: {round_list(static_start_position, 0)}")
else:
    print("Could not determine Static Start Position")
    sys.exit()


while True:
    xyz_position, orientation = get_xyz_position_orientation(vicontracker, OBJECT_NAME)
    distance_from_startpoint = get_3d_dist_between_points(static_start_position, xyz_position)

    print(f"XYZ: {round_list(xyz_position, 0)} Orientation Rad/Deg.: {orientation:.4f}/{math.degrees(orientation):.4f}, Distance from start: {distance_from_startpoint:.0f} mm     ", end="\r")
    time.sleep(0.1)