import matplotlib.pyplot
from mpl_toolkits.mplot3d import Axes3D
ax = matplotlib.pyplot.figure().add_subplot(111, projection='3d')
from ikpy.chain import Chain
from ikpy.link import OriginLink, URDFLink

JNV1_chain = Chain.from_urdf_file("C://Users//Justin Nguyen//Desktop//RobotArmProject//Code//InverseKinematics//armURDF.urdf", active_links_mask=[False, True, True, False, True, True, True, True])

JNV1_chain.plot(JNV1_chain.inverse_kinematics([360, 100, 150]), ax)
matplotlib.pyplot.show()