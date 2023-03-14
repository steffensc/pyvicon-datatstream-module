import pyvicon_datastream as pv

class ObjectTracker:
    def __init__(self, ip):
        self.ip = ip
    
        self.is_connected = False

        self.vicon_client = pv.PyViconDatastream()
        self.connect()

        if self.is_connected == True:
            self.vicon_client.enable_segment_data()
            self.vicon_client.set_stream_mode(pv.StreamMode.ServerPush)
            self.vicon_client.set_axis_mapping(pv.Direction.Forward, pv.Direction.Left, pv.Direction.Up)

    def _get_object_position(self, name):
        subject_count = self.vicon_client.get_subject_count()
        positions = []
        for subj_idx in range(subject_count):
            subject_name = self.vicon_client.get_subject_name(subj_idx)

            if subject_name != name: #Skip objects we are not interessted in
                continue
            
            segment_count = self.vicon_client.get_segment_count(name)
            for seg_idx in range(segment_count):
                segment_name = self.vicon_client.get_segment_name(subject_name, seg_idx)
                segment_global_translation = self.vicon_client.get_segment_global_translation(subject_name, segment_name)
                segment_local_rotation     = self.vicon_client.get_segment_local_rotation_euler_xyz(subject_name, segment_name)

                if segment_global_translation is not None and segment_local_rotation is not None:
                    position_x = segment_global_translation[0]
                    position_y = segment_global_translation[1]
                    position_z = segment_global_translation[2]
                    euler_x = segment_local_rotation[0]
                    euler_y = segment_local_rotation[1]
                    euler_z = segment_local_rotation[2]

                    position_entry = [
                        subject_name, 
                        segment_name, 
                        position_x,
                        position_y,
                        position_z,
                        euler_x,
                        euler_y,
                        euler_z
                    ]
                    positions.append(position_entry)
        return positions

    def connect(self, ip=None):
        if ip is not None: # set
            print(f"Changing IP of Vicon Host to: {ip}")
            self.ip = ip
        
        ret = self.vicon_client.connect(self.ip)
        if ret != pv.Result.Success:
            print(f"Connection to {self.ip} failed")
            self.is_connected = False
        else:
            print(f"Connection to {self.ip} successful")
            self.is_connected = True
        return self.is_connected

    def get_position(self, object_name):
        if self.is_connected == True:
            frame = self.vicon_client.get_frame()
            if frame == pv.Result.Success:
                latency     = self.vicon_client.get_latency_total()
                framenumber = self.vicon_client.get_frame_number()
                position    = self._get_object_position(object_name)
                return latency, framenumber, position
        return False

    def get_framerate(self):
        return self.vicon_client.get_frame_rate()

    def get_framenumber(self):
        return self.vicon_client.get_frame_number()

    def get_timecode(self):
        return self.vicon_client.get_time_code()
