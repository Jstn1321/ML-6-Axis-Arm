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
    
    print(invKine)
    
    for i in range(0,len(invKine)):
        invKine[i] = math.degrees(invKine[i])
    """
    print(invKine)
    
    invKine[1] = (invKine[1]/360) * (51 * 1600 * 3)
    invKine[2] = (invKine[2]/360) * (15* 1600)
    invKine[4] = (invKine[4]/360) * 27* 1600 * 3
    invKine[5] = (invKine[5]/360) * (5 * 1600 * 3)
    invKine[6] = (invKine[6]/360) * 14 * 1600 * 3
    invKine[7] = (invKine[7]/360) * (1600)
     """
    for i in range(0,len(invKine)):
        invKine[i] = int(invKine[i])
    
    print(invKine)

    return invKine

#ik([0.4,0.0,0.2])
#Z,X,Y