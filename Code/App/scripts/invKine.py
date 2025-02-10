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
        invKine[0] = (invKine[0]/360) * (51 * 1600)
        invKine[1] = (invKine[1]/360) * (15* 1600)
        invKine[2] = (invKine[2]/360) * 27* 1600
        invKine[3] = (invKine[3]/360) * (5 * 1600)
        invKine[4] = (invKine[4]/360) * 14 * 1600
        invKine[5] = (invKine[5]/360) * (1600)
    print(invKine)
    return invKine
"""
JNV1_chain.plot(JNV1_chain.inverse_kinematics(target_position=[0.2,0.4,0.3], target_orientation=target_orientation,orientation_mode=orientation_axis), ax)
matplotlib.pyplot.show()
print(JNV1_chain.inverse_kinematics(target_position=[0.2,0.4,0.3], target_orientation=target_orientation,orientation_mode=orientation_axis))
print(ik([0.5,0.3,0.6]))
"""