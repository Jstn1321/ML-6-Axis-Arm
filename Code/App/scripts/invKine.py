import ikpy.chain
import matplotlib.pyplot
import matplotlib as plt
from mpl_toolkits.mplot3d import Axes3D
ax = matplotlib.pyplot.figure().add_subplot(111, projection='3d')
import ikpy.chain
import numpy as np
import ikpy.utils.plot as plot_utils
from ikpy.chain import Chain
from ikpy.link import OriginLink, URDFLink
import math
JNV1_chain = ikpy.chain.Chain.from_urdf_file(r"C:\Nerd Projects\RobotArmProject\Code\App\scripts\assets\URDF\armURDF.urdf", active_links_mask=[False, True, True, False, True, True, True, True])
#MAX EXTENSION LENGTH: 71.5cm
np.set_printoptions(suppress=True, precision=6)
target_orientation = [0, 0, -1]
orientation_axis = "Z"
def ik(xyz):
    invKine = JNV1_chain.inverse_kinematics(target_position=xyz, target_orientation=target_orientation,orientation_mode=orientation_axis).tolist()
    for i in range(0,len(invKine)):
        invKine[i] = math.degrees(invKine[i])
    invKine[0] = (invKine[0]/360) * (50 + (4397/4913))* 1600
    invKine[1] = (invKine[1]/360) * (15 + (3/10))* 1600
    invKine[2] = (invKine[2]/360) * (26 + (103/121))* 1600
    invKine[3] = (invKine[3]/360) * (5 + (2/11))* 1600
    invKine[4] = (invKine[4]/360) * (13.73) * 1600
    invKine[5] = (invKine[5]/360) * (1600)
    return invKine
"""
target_position = [0.2 ,0.1, 0.54]
target_orientation = [0, -1, 0]
print("The angles of each joints are : ", JNV1_chain.inverse_kinematics(target_position, target_orientation))

real_frame = JNV1_chain.forward_kinematics(JNV1_chain.inverse_kinematics(target_position, target_orientation))
print("Computed position vector : %s, original position vector : %s" % (real_frame[:3, 3], target_position))

JNV1_chain.plot(JNV1_chain.inverse_kinematics(target_position, target_orientation), ax)
matplotlib.pyplot.show()
"""
