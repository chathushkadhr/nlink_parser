import os

from launch import LaunchDescription
from launch_ros.actions import Node
from launch_ros.descriptions import ParameterFile
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.actions import TimerAction

 
 
    
def generate_launch_description():
    
    pkg_dir = get_package_share_directory("nlink_parser")

    rviz_converter= Node(
            package='nlink_parser',
            executable='rviz_uwb',
            name='rviz_converter',
            # namespace=namespace,
            # remappings=remappings,
            output="screen",
            # parameters=[ {'use_sim_time': use_sim_time},
             #ParameterFile(os.path.join(pkg_dir, 'config', 'params.yaml'), allow_substs=True)],
            # prefix=['xterm -e gdb -ex run --args'],
            # arguments=['--ros-args', '--log-level', 'debug'],
            # emulate_tty=True   
        )
    
    rviz = Node(
            package='rviz2',
            executable='rviz2',
            name='UWB_rviz',
            # namespace=namespace,
            # remappings=remappings,
            output="screen",
            arguments=['-d', [os.path.join(pkg_dir, 'rviz', 'default_view.rviz')]]
            # parameters=[ {'use_sim_time': use_sim_time},
             #ParameterFile(os.path.join(pkg_dir, 'config', 'params.yaml'), allow_substs=True)],
            # prefix=['xterm -e gdb -ex run --args'],
            # arguments=['--ros-args', '--log-level', 'debug'],
            # emulate_tty=True   
        )
   
    tf= Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='base2linktrack',
            # namespace=namespace,
            # remappings=remappings,
            output="screen",
            # parameters=[ {'use_sim_time': use_sim_time},
             #ParameterFile(os.path.join(pkg_dir, 'config', 'params.yaml'), allow_substs=True)],
            # prefix=['xterm -e gdb -ex run --args'],
            arguments = ["0","0", "0", "0", "0", "0", "1", "/map", "/linktrack_map"]
            # emulate_tty=True   
        )
    
    ld = LaunchDescription()
    # ld.add_action(declare_arg_sim_time)
    # ld.add_action(declare_arg_namespace)
    # ld.add_action(declare_arg_index)
    ld.add_action(rviz_converter)
    ld.add_action(rviz)
    ld.add_action(tf)


    
    return ld
