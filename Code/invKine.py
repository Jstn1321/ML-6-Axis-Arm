import ikpy.chain
import matplotlib.pyplot
import matplotlib as plt
from jedi.api.refactoring import inline
from mpl_toolkits.mplot3d import Axes3D
ax = matplotlib.pyplot.figure().add_subplot(111, projection='3d')
import ikpy.chain
import numpy as np
import ikpy.utils.plot as plot_utils
from ikpy.chain import Chain
from ikpy.link import OriginLink, URDFLink
JNV1_chain = ikpy.chain.Chain.from_urdf_file(r"C:\Users\Justin Nguyen\Desktop\RobotArmProject\Code\InverseKinematics\armURDF.urdf", active_links_mask=[False, True, True, False, True, True, True, True])
#MAX EXTENSION LENGTH: 71.5cm
def invKine(xyz):
    return JNV1_chain.inverse_kinematics(xyz)
target_position = [0.2 ,0.1, 0.54]
target_orientation = [0, -1, 0]
print("The angles of each joints are : ", JNV1_chain.inverse_kinematics(target_position, target_orientation))

real_frame = JNV1_chain.forward_kinematics(JNV1_chain.inverse_kinematics(target_position, target_orientation))
print("Computed position vector : %s, original position vector : %s" % (real_frame[:3, 3], target_position))

JNV1_chain.plot(JNV1_chain.inverse_kinematics(target_position, target_orientation), ax)
matplotlib.pyplot.show()
