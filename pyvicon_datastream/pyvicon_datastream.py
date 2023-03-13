import pyvicon_datastream._pyvicon_datastream_wrapper as datastream_wrapper

from enum import Enum
import numpy as np  

class Result(Enum):
    Unknown = 0
    NotImplemented = 1
    Success = 2
    InvalidHostName = 3
    InvalidMulticastIP = 4
    ClientAlreadyConnected = 5
    ClientConnectionFailed = 6
    ServerAlreadyTransmittingMulticast = 7
    ServerNotTransmittingMulticast = 8
    NotConnected = 9
    NoFrame = 10
    InvalidIndex = 11
    InvalidCameraName = 12
    InvalidSubjectName = 13
    InvalidSegmentName = 14
    InvalidMarkerName = 15
    InvalidDeviceName = 16
    InvalidDeviceOutputName = 17
    InvalidLatencySampleName = 18
    CoLinearAxes = 19
    LeftHandedAxes = 20
    HapticAlreadySet = 21


class StreamMode(Enum):
    ClientPull = 0
    ClientPullPreFetch = 1
    ServerPush = 2


class Direction(Enum):
    Up = 0
    Down = 1
    Left = 2
    Right = 3
    Forward = 4
    Backward = 5


class TimecodeStandard(Enum):
    NONE = 0
    PAL = 1
    NTSC = 2
    NTSCDrop= 3
    Film = 4


class PyViconDatastream:
    def __init__(self):
        self.client_ = datastream_wrapper.new_client()
        major, minor, point = datastream_wrapper.pyvicon_version(self.client_)
        self.__version__ = "{}.{}.{}".format(major, minor, point)

    def connect(self, ip):
        return Result(datastream_wrapper.pyvicon_connect(self.client_, ip))

    def connect_multicast(self, ip, multicast):
        return Result(datastream_wrapper.pyvicon_connect_to_multicast(self.client_, ip, multicast))

    def disconnect(self):
        return Result(datastream_wrapper.pyvicon_disconnect(self.client_))

    def is_connected(self):
        return datastream_wrapper.pyvicon_isconnected(self.client_)

    def start_server_multicast(self, server_ip, multicast_ip):
        return Result(datastream_wrapper.pyvicon_start_transmitting_multicast(self.client_, server_ip, multicast_ip))

    def stop_server_multicast(self):
        return Result(datastream_wrapper.pyvicon_stop_transmitting_multicast(self.client_))

    def enable_segment_data(self):
        return Result(datastream_wrapper.pyvicon_enable_segment_data(self.client_))

    def enable_marker_data(self):
        return Result(datastream_wrapper.pyvicon_enable_marker_data(self.client_))

    def enable_unlabeled_marker_data(self):
        return Result(datastream_wrapper.pyvicon_enable_unlabeled_marker_data(self.client_))

    def enable_device_data(self):
        return Result(datastream_wrapper.pyvicon_enable_device_data(self.client_))

    def disable_segment_data(self):
        return Result(datastream_wrapper.pyvicon_disable_segment_data(self.client_))

    def disable_marker_data(self):
        return Result(datastream_wrapper.pyvicon_disable_marker_data(self.client_))

    def disable_unlabeled_marker_data(self):
        return Result(datastream_wrapper.pyvicon_disable_unlabeled_marker_data(self.client_))

    def disable_device_data(self):
        return Result(datastream_wrapper.pyvicon_disable_device_data(self.client_))

    def is_marker_data_enabled(self):
        return datastream_wrapper.pyvicon_is_marker_data_enabled(self.client_)

    def is_unlabeled_marker_data_enabled(self):
        return datastream_wrapper.pyvicon_is_unlabeled_marker_data_enabled(self.client_)

    def is_device_data_enabled(self):
        return datastream_wrapper.pyvicon_is_device_data_enabled(self.client_)

    def set_buffer_size(self, size):
        datastream_wrapper.pyvicon_set_buffer_size(self.client_, size)

    def set_stream_mode(self, stream_mode):
        self.check_enum(stream_mode, StreamMode, "set_stream_mode")
        return Result(datastream_wrapper.pyvicon_set_stream_mode(self.client_, stream_mode.value))

    def set_axis_mapping(self, X, Y, Z):
        """
        Common : Z-up (Forward, Left, Up)
                 Y-up (Forward, Up, Right)
        """
        self.check_enum(X, Direction, "set_axis_mapping")
        self.check_enum(Y, Direction, "set_axis_mapping")
        self.check_enum(Z, Direction, "set_axis_mapping")
        return Result(datastream_wrapper.pyvicon_set_axis_mapping(self.client_, X.value, Y.value, Z.value))

    def get_axis_mapping(self):
        X, Y, Z = datastream_wrapper.pyvicon_get_axis_mapping(self.client_)
        return Direction(X), Direction(Y), Direction(Z)

    def get_frame(self):
        return Result(datastream_wrapper.pyvicon_get_frame(self.client_))

    def get_frame_number(self):
        return datastream_wrapper.pyvicon_get_frame_number(self.client_)

    def get_time_code(self):
        result, standard, hours, minutes, seconds = datastream_wrapper.pyvicon_get_time_code(self.client_)
        return Result(result), TimecodeStandard(standard), hours, minutes, seconds

    def get_frame_rate(self):
        return datastream_wrapper.pyvicon_get_frame_rate(self.client_)

    def get_latency_total(self):
        return datastream_wrapper.pyvicon_get_latency_total(self.client_)

    def get_subject_count(self):
        return datastream_wrapper.pyvicon_get_subject_count(self.client_)

    def get_subject_name(self, index):
        return datastream_wrapper.pyvicon_get_subject_name(self.client_, index)

    def get_subject_root_segment_name(self, name):
        return datastream_wrapper.pyvicon_get_subject_root_segment_name(self.client_, name)

    def get_segment_count(self, name):
        return datastream_wrapper.pyvicon_get_segment_count(self.client_, name)

    def get_segment_name(self, name, index):
        return datastream_wrapper.pyvicon_get_segment_name(self.client_, name, index)

    def get_segment_global_translation(self, subject_name, segment_name):
        T = datastream_wrapper.pyvicon_get_segment_global_translation(self.client_, subject_name, segment_name)
        if T is None:
            return None
        return np.array(T)

    def get_segment_global_rotation_matrix(self, subject_name, segment_name):
        matrix = datastream_wrapper.pyvicon_get_segment_global_rotation_matrix(self.client_, subject_name, segment_name)
        if matrix is None:
            return None
        return np.array(matrix).reshape((3, 3))

    def get_segment_global_rotation_euler_xyz(self, subject_name, segment_name):
        euler_xyz = datastream_wrapper.pyvicon_get_segment_global_rotation_euler_xyz(self.client_, subject_name, segment_name)
        if euler_xyz is None:
            return None
        return np.array(euler_xyz)

    def get_segment_global_rotation_helical(self, subject_name, segment_name):
        helical = datastream_wrapper.pyvicon_get_segment_global_rotation_helical(self.client_, subject_name, segment_name)
        if helical is None:
            return None
        return np.array(helical)

    def get_segment_global_quaternion(self, subject_name, segment_name):
        """
        Return the quaternion as : w,x,y,z
        :param subject_name:
        :param segment_name:
        :return:
        """
        quaternion = datastream_wrapper.pyvicon_get_segment_global_quaternion(self.client_, subject_name, segment_name)
        if quaternion is None:
            return None
        return np.array(quaternion)

    def get_segment_local_translation(self, subject_name, segment_name):
        T = datastream_wrapper.pyvicon_get_segment_local_translation(self.client_, subject_name, segment_name)
        if T is None:
            return None
        return np.array(T)

    def get_segment_local_rotation_euler_xyz(self, subject_name, segment_name):
        euler_xyz = datastream_wrapper.pyvicon_get_segment_local_rotation_euler_xyz(self.client_, subject_name, segment_name)
        if euler_xyz is None:
            return None
        return np.array(euler_xyz)

    def get_subject_quality(self, name):
        return datastream_wrapper.pyvicon_get_object_quality(self.client_, name)

    def get_marker_count(self, name):
        return datastream_wrapper.pyvicon_get_marker_count(self.client_, name)

    def get_marker_name(self, name, index):
        return datastream_wrapper.pyvicon_get_marker_name(self.client_, name, index)

    def get_marker_global_translation(self, subject_name, marker_name):
        pose = datastream_wrapper.pyvicon_get_marker_global_translation(self.client_, subject_name, marker_name)
        if pose is None:
            return None
        return np.array(pose)

    def get_unlabeled_marker_count(self):
        return datastream_wrapper.pyvicon_get_unlabeled_marker_count(self.client_)

    def get_unlabeled_marker_global_translation(self, index):
        return datastream_wrapper.pyvicon_get_unlabeled_marker_global_translation(self.client_, index)

    def get_camera_count(self):
        return datastream_wrapper.pyvicon_get_camera_count(self.client_)

    def get_camera_name(self, index):
        return datastream_wrapper.pyvicon_get_camera_name(self.client_, index)

    @staticmethod
    def check_enum(value, enum, method):
        if not isinstance(value, enum):
            raise RuntimeError("{} expect a {}, received a {}".format(method, enum, type(value)))

if __name__ == '__main__':
    test = PyViconDatastream()
    print("SDK version : {}".format(test.__version__))
    print("Connection status : {}".format(test.is_connected()))
    print(test.connect("127.0.0.1"))
    print(test.connect_multicast("127.0.0.1", "224.0.0.0"))
    print(test.disconnect())
    print(test.start_server_multicast("localhost", "224.0.0.0"))
    print(test.stop_server_multicast())
    print(test.set_stream_mode(StreamMode.ClientPull))
    print(test.get_axis_mapping())
    print(test.get_subject_name(0))
