#include <Python.h>
#include <string>
#include <iostream>
#include "DataStreamClient.h"

using namespace ViconDataStreamSDK;
using namespace CPP;

#define CLIENT_NAME "pyvicon_datastream.client"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    //################
    //Module wrapped functions
    //################

    void destroy_client(PyObject* client){
        delete (Client*)PyCapsule_GetPointer(client, CLIENT_NAME);
    }

    static PyObject* new_client(PyObject* self, PyObject* args){
        return PyCapsule_New(new Client(), CLIENT_NAME, destroy_client);
    }

    static PyObject* pyvicon_version(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;

        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);
        Output_GetVersion out = client->GetVersion();
        return Py_BuildValue("III", out.Major, out.Minor, out.Point);
    }

    //###################
    //Connection handling
    //###################

    static PyObject* pyvicon_connect(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* ip;
        if (!PyArg_ParseTuple(args, "Os", &capsule, &ip)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        //Release GIL for io
        Output_Connect out;
        Py_BEGIN_ALLOW_THREADS
        out = client->Connect(ip);
        Py_END_ALLOW_THREADS
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_connect_to_multicast(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* ip;
        char* multicast;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &ip, &multicast)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        //Release GIL for io
        Output_ConnectToMulticast out;
        Py_BEGIN_ALLOW_THREADS
        out = client->ConnectToMulticast(ip, multicast);
        Py_END_ALLOW_THREADS
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_disconnect(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_Disconnect out;
        out = client->Disconnect();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_isconnected(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;

        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);
        if (client->IsConnected().Connected)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    }
    static PyObject* pyvicon_start_transmitting_multicast(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* server_ip;
        char* multicast_ip;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &server_ip, &multicast_ip)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        //Release GIL for io
        Output_StartTransmittingMulticast out;
        Py_BEGIN_ALLOW_THREADS
        out = client->StartTransmittingMulticast(server_ip, multicast_ip);
        Py_END_ALLOW_THREADS
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_stop_transmitting_multicast(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        //Release GIL for io
        Output_StopTransmittingMulticast out;
        Py_BEGIN_ALLOW_THREADS
        out = client->StopTransmittingMulticast();
        Py_END_ALLOW_THREADS
        return Py_BuildValue("I", out.Result);
    }

    //###################
    // Configurations
    //###################

    static PyObject* pyvicon_enable_segment_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_EnableSegmentData out;
        out = client->EnableSegmentData();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_enable_marker_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_EnableMarkerData out;
        out = client->EnableMarkerData();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_enable_unlabeled_marker_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_EnableUnlabeledMarkerData out;
        out = client->EnableUnlabeledMarkerData();
        return Py_BuildValue("I", out.Result);
    }
    // Output_EnableMarkerRayData       EnableMarkerRayData();
    static PyObject* pyvicon_enable_device_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_EnableDeviceData out;
        out = client->EnableDeviceData();
        return Py_BuildValue("I", out.Result);
    }
    // Output_EnableCentroidData        EnableCentroidData();
    // Output_EnableGreyscaleData       EnableGreyscaleData();
    // Output_EnableDebugData           EnableDebugData();

    static PyObject* pyvicon_disable_segment_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_DisableSegmentData out;
        out = client->DisableSegmentData();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_disable_marker_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_DisableMarkerData out;
        out = client->DisableMarkerData();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_disable_unlabeled_marker_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_DisableUnlabeledMarkerData out;
        out = client->DisableUnlabeledMarkerData();
        return Py_BuildValue("I", out.Result);
    }
    // Output_DisableMarkerRayData       DisableMarkerRayData();
    static PyObject* pyvicon_disable_device_data(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_DisableDeviceData out;
        out = client->DisableDeviceData();
        return Py_BuildValue("I", out.Result);
    }
    // Output_DisableCentroidData        DisableCentroidData();
    // Output_DisableGreyscaleData       DisableGreyscaleData();
    // Output_DisableDebugData           DisableDebugData();

    // Output_IsSegmentDataEnabled         IsSegmentDataEnabled() const;
    static PyObject* pyvicon_is_marker_data_enabled(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_IsMarkerDataEnabled out;
        out = client->IsMarkerDataEnabled();
        if(out.Enabled)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    }
    static PyObject* pyvicon_is_unlabeled_marker_data_enabled(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_IsUnlabeledMarkerDataEnabled out;
        out = client->IsUnlabeledMarkerDataEnabled();
        if(out.Enabled)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    }
    // Output_IsMarkerRayDataEnabled       IsMarkerRayDataEnabled() const;
    static PyObject* pyvicon_is_device_data_enabled(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_IsDeviceDataEnabled out;
        out = client->IsDeviceDataEnabled();
        if(out.Enabled)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    }
    // Output_IsCentroidDataEnabled        IsCentroidDataEnabled() const;
    // Output_IsGreyscaleDataEnabled       IsGreyscaleDataEnabled() const;
    // Output_IsDebugDataEnabled           IsDebugDataEnabled() const;

    //###################
    //Data Acquisition
    //###################

    static PyObject* pyvicon_set_buffer_size(PyObject* self, PyObject* args) {
        PyObject* capsule;
        unsigned int size;
        if (!PyArg_ParseTuple(args, "OI", &capsule, &size)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        client->SetBufferSize(size);
        Py_RETURN_NONE;
    }
    static PyObject* pyvicon_set_stream_mode(PyObject* self, PyObject* args) {
        PyObject* capsule;
        unsigned int stream_mode;
        if (!PyArg_ParseTuple(args, "OI", &capsule, &stream_mode)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_SetStreamMode out;
        out = client->SetStreamMode(static_cast<StreamMode::Enum>(stream_mode));
        return Py_BuildValue("I", out.Result);
    }
    // Output_SetApexDeviceFeedback SetApexDeviceFeedback( const String& i_rDeviceName, bool i_bOn );
    static PyObject* pyvicon_set_axis_mapping(PyObject* self, PyObject* args) {
        PyObject* capsule;
        unsigned int X;
        unsigned int Y;
        unsigned int Z;
        if (!PyArg_ParseTuple(args, "OIII", &capsule, &X, &Y, &Z)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_SetAxisMapping out;
        out = client->SetAxisMapping(static_cast<Direction::Enum>(X),
                                     static_cast<Direction::Enum>(Y),
                                     static_cast<Direction::Enum>(Z));
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_get_axis_mapping(PyObject* self, PyObject* args) {
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetAxisMapping out;
        out = client->GetAxisMapping();
        return Py_BuildValue("III", out.XAxis, out.YAxis, out.ZAxis);
    }
    // Output_GetServerOrientation GetServerOrientation() const;
    static PyObject* pyvicon_get_frame(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetFrame out;
        out = client->GetFrame();
        return Py_BuildValue("I", out.Result);
    }
    static PyObject* pyvicon_get_frame_number(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetFrameNumber out;
        out = client->GetFrameNumber();
        return Py_BuildValue("I", out.FrameNumber);
    }
    static PyObject* pyvicon_get_time_code(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetTimecode out;
        out = client->GetTimecode();
        return Py_BuildValue("IIIII",out.Result, out.Standard, out.Hours, out.Minutes, out.Seconds);
    }
    static PyObject* pyvicon_get_frame_rate(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetFrameRate out;
        out = client->GetFrameRate();
        return Py_BuildValue("d", out.FrameRateHz);
    }
    // Output_GetLatencySampleCount  GetLatencySampleCount() const;
    // Output_GetLatencySampleName   GetLatencySampleName( const unsigned int LatencySampleIndex ) const;
    // Output_GetLatencySampleValue  GetLatencySampleValue( const String & LatencySampleName ) const;
    static PyObject* pyvicon_get_latency_total(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetLatencyTotal out;
        out = client->GetLatencyTotal();
        return Py_BuildValue("d", out.Total);
    }
    // Output_GetHardwareFrameNumber GetHardwareFrameNumber() const;
    // Output_GetFrameRateCount  GetFrameRateCount() const;
    // Output_GetFrameRateName   GetFrameRateName( const unsigned int FrameRateIndex ) const;
    // Output_GetFrameRateValue  GetFrameRateValue( const String & FrameRateName ) const;
    static PyObject* pyvicon_get_subject_count(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetSubjectCount out;
        out = client->GetSubjectCount();
        return Py_BuildValue("I", out.SubjectCount);
    }
    static PyObject* pyvicon_get_subject_name(PyObject* self, PyObject* args){
        PyObject* capsule;
        unsigned int index;
        if (!PyArg_ParseTuple(args, "OI", &capsule, &index)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSubjectName out = client->GetSubjectName(index);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        std::string name_str = (std::string)out.SubjectName;
        return Py_BuildValue("s", name_str.c_str());
    }
    static PyObject* pyvicon_get_subject_root_segment_name(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        if (!PyArg_ParseTuple(args, "Os", &capsule, &name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSubjectRootSegmentName out = client->GetSubjectRootSegmentName(name);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        std::string name_str = (std::string)out.SegmentName;
        return Py_BuildValue("s", name_str.c_str());
    }

    // Output_GetSegmentCount GetSegmentCount( const String  & SubjectName ) const;
    static PyObject* pyvicon_get_segment_count(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        if (!PyArg_ParseTuple(args, "Os", &capsule, &name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentCount out = client->GetSegmentCount(name);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("I", out.SegmentCount);
    }
    
    // Output_GetSegmentName GetSegmentName( const String       & SubjectName, const unsigned int   SegmentIndex ) const;
    static PyObject* pyvicon_get_segment_name(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        unsigned int index;
        if (!PyArg_ParseTuple(args, "OsI", &capsule, &name, &index)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentName out = client->GetSegmentName(name, index);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        std::string name_str = (std::string)out.SegmentName;
        return Py_BuildValue("s", name_str.c_str());
    }
    
    // Output_GetSegmentChildCount GetSegmentChildCount( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentChildName GetSegmentChildName( const String       & SubjectName, const String       & SegmentName, const unsigned int   SegmentIndex ) const;
    // Output_GetSegmentParentName GetSegmentParentName( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentStaticTranslation GetSegmentStaticTranslation( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentStaticRotationHelical GetSegmentStaticRotationHelical( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentStaticRotationMatrix GetSegmentStaticRotationMatrix( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentStaticRotationQuaternion GetSegmentStaticRotationQuaternion( const String & SubjectName, const String & SegmentName ) const;
    // Output_GetSegmentStaticRotationEulerXYZ GetSegmentStaticRotationEulerXYZ( const String & SubjectName, const String & SegmentName ) const;

    static PyObject* pyvicon_get_segment_global_translation(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentGlobalTranslation out = client->GetSegmentGlobalTranslation(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Translation[0], out.Translation[1], out.Translation[2]);
    }

    static PyObject* pyvicon_get_segment_global_rotation_matrix(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentGlobalRotationMatrix out = client->GetSegmentGlobalRotationMatrix(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddddddddd", out.Rotation[0], out.Rotation[1], out.Rotation[2],
                                          out.Rotation[3], out.Rotation[4], out.Rotation[5],
                                          out.Rotation[6], out.Rotation[7], out.Rotation[8]);
    }

    static PyObject* pyvicon_get_segment_global_rotation_euler_xyz(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentGlobalRotationEulerXYZ out = client->GetSegmentGlobalRotationEulerXYZ(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Rotation[0], out.Rotation[1], out.Rotation[2]);
    }

    static PyObject* pyvicon_get_segment_global_rotation_helical(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentGlobalRotationHelical out = client->GetSegmentGlobalRotationHelical(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Rotation[0], out.Rotation[1], out.Rotation[2]);
    }

    static PyObject* pyvicon_get_segment_global_quaternion(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentGlobalRotationQuaternion out = client->GetSegmentGlobalRotationQuaternion(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("dddd", out.Rotation[3], out.Rotation[0], out.Rotation[1], out.Rotation[2]);
    }

    static PyObject* pyvicon_get_segment_local_translation(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentLocalTranslation out = client->GetSegmentLocalTranslation(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Translation[0], out.Translation[1], out.Translation[2]);
    }

    // Output_GetSegmentLocalRotationHelical GetSegmentLocalRotationHelical( const String & SubjectName, const String & SegmentName ) const;

    // Output_GetSegmentLocalRotationMatrix GetSegmentLocalRotationMatrix( const String & SubjectName, const String & SegmentName ) const;

    // Output_GetSegmentLocalRotationQuaternion GetSegmentLocalRotationQuaternion( const String & SubjectName, const String & SegmentName ) const;

    // Output_GetSegmentLocalRotationEulerXYZ GetSegmentLocalRotationEulerXYZ( const String & SubjectName, const String & SegmentName ) const;
    static PyObject* pyvicon_get_segment_local_rotation_euler_xyz(PyObject* self, PyObject* args) {
        PyObject* capsule;
        char* subject_name;
        char* segment_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &segment_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetSegmentLocalRotationEulerXYZ out = client->GetSegmentLocalRotationEulerXYZ(subject_name, segment_name);
        if(out.Result != Result::Success || out.Occluded) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Rotation[0], out.Rotation[1], out.Rotation[2]);
    }

    static PyObject* pyvicon_get_object_quality(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        if (!PyArg_ParseTuple(args, "Os", &capsule, &name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetObjectQuality out;
        out = client->GetObjectQuality(name);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("d", out.Quality);
    }

    static PyObject* pyvicon_get_marker_count(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        if (!PyArg_ParseTuple(args, "Os", &capsule, &name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetMarkerCount out;
        out = client->GetMarkerCount(name);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("I", out.MarkerCount);
    }
    static PyObject* pyvicon_get_marker_name(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* name;
        unsigned int index;
        if (!PyArg_ParseTuple(args, "OsI", &capsule, &name, &index)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        // Watch out with Vicon's custom string memory management!!!!
        Output_GetMarkerName out = client->GetMarkerName(name, index);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        std::string name_str = (std::string)out.MarkerName;
        return Py_BuildValue("s", name_str.c_str());
    }
    // Output_GetMarkerParentName GetMarkerParentName( const String & SubjectName, const String & MarkerName ) const;
    static PyObject* pyvicon_get_marker_global_translation(PyObject* self, PyObject* args){
        PyObject* capsule;
        char* subject_name;
        char* marker_name;
        if (!PyArg_ParseTuple(args, "Oss", &capsule, &subject_name, &marker_name)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetMarkerGlobalTranslation out;
        out = client->GetMarkerGlobalTranslation(subject_name, marker_name);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        if(out.Occluded){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Translation[0], out.Translation[1], out.Translation[2]);
    }
    // Output_GetMarkerRayContributionCount GetMarkerRayContributionCount( const String & SubjectName, const String & MarkerName ) const;
    // Output_GetMarkerRayContribution GetMarkerRayContribution( const String & SubjectName, const String & MarkerName, unsigned int MarkerRayContributionIndex ) const;
    static PyObject* pyvicon_get_unlabeled_marker_count(PyObject* self, PyObject* args){
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetUnlabeledMarkerCount out;
        out = client->GetUnlabeledMarkerCount();
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("I", out.MarkerCount);
    }
    static PyObject* pyvicon_get_unlabeled_marker_global_translation(PyObject* self, PyObject* args){
        PyObject* capsule;
        unsigned int index;
        if (!PyArg_ParseTuple(args, "OI", &capsule, &index)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetUnlabeledMarkerGlobalTranslation out;
        out = client->GetUnlabeledMarkerGlobalTranslation(index);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        return Py_BuildValue("ddd", out.Translation[0], out.Translation[1], out.Translation[2]);
    }
    // Output_GetLabeledMarkerCount GetLabeledMarkerCount() const;
    // Output_GetLabeledMarkerGlobalTranslation GetLabeledMarkerGlobalTranslation( const unsigned int MarkerIndex ) const;
    // Output_GetDeviceCount GetDeviceCount() const;
    // Output_GetDeviceName  GetDeviceName( const unsigned int DeviceIndex ) const;
    // Output_GetDeviceOutputCount GetDeviceOutputCount( const String  & DeviceName ) const;
    // Output_GetDeviceOutputName GetDeviceOutputName( const String  & DeviceName, const unsigned int   DeviceOutputIndex ) const;
    // Output_GetDeviceOutputValue GetDeviceOutputValue( const String & DeviceName, const String & DeviceOutputName ) const;
    // Output_GetDeviceOutputSubsamples GetDeviceOutputSubsamples( const String & DeviceName, const String & DeviceOutputName ) const;
    // Output_GetDeviceOutputValue GetDeviceOutputValue( const String & DeviceName, const String & DeviceOutputName, const unsigned int Subsample ) const;
    // Output_GetForcePlateCount GetForcePlateCount() const;
    // Output_GetGlobalForceVector GetGlobalForceVector( const unsigned int ForcePlateIndex ) const;
    // Output_GetGlobalMomentVector GetGlobalMomentVector( const unsigned int ForcePlateIndex ) const;
    // Output_GetGlobalCentreOfPressure GetGlobalCentreOfPressure( const unsigned int ForcePlateIndex ) const;
    // Output_GetForcePlateSubsamples GetForcePlateSubsamples( const unsigned int ForcePlateIndex ) const;
    // Output_GetGlobalForceVector GetGlobalForceVector( const unsigned int ForcePlateIndex, const unsigned int Subsample ) const;
    // Output_GetGlobalMomentVector GetGlobalMomentVector( const unsigned int ForcePlateIndex, const unsigned int Subsample ) const;
    // Output_GetGlobalCentreOfPressure GetGlobalCentreOfPressure( const unsigned int ForcePlateIndex, const unsigned int Subsample ) const;
    // Output_GetEyeTrackerCount GetEyeTrackerCount() const;
    // Output_GetEyeTrackerGlobalPosition GetEyeTrackerGlobalPosition( const unsigned int EyeTrackerIndex ) const;
    // Output_GetEyeTrackerGlobalGazeVector GetEyeTrackerGlobalGazeVector( const unsigned int EyeTrackerIndex ) const;

    static PyObject* pyvicon_get_camera_count(PyObject* self, PyObject* args) {
        PyObject* capsule;
        if (!PyArg_ParseTuple(args, "O", &capsule)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetCameraCount out;
        out = client->GetCameraCount();
        return Py_BuildValue("I", out.CameraCount);
    }
    static PyObject* pyvicon_get_camera_name(PyObject* self, PyObject* args){
        PyObject* capsule;
        unsigned int index;
        if (!PyArg_ParseTuple(args, "OI", &capsule, &index)) return NULL;
        Client* client = (Client*)PyCapsule_GetPointer(capsule, CLIENT_NAME);

        Output_GetCameraName out = client->GetCameraName(index);
        if(out.Result != Result::Success){
            Py_RETURN_NONE;
        }
        std::string name_str = (std::string)out.CameraName;
        return Py_BuildValue("s", name_str.c_str());
    }
    // Output_GetCameraId GetCameraId( const std::string & i_rCameraName ) const;
    // Output_GetCameraUserId GetCameraUserId( const std::string & i_rCameraName ) const;
    // Output_GetCameraType GetCameraType( const std::string & i_rCameraName ) const;
    // Output_GetCameraDisplayName GetCameraDisplayName(  const std::string & i_rCameraName ) const;
    // Output_GetCameraResolution GetCameraResolution( const std::string & i_rCameraName ) const;
    // Output_GetIsVideoCamera GetIsVideoCamera( const std::string & i_rCameraName ) const;
    // Output_GetCentroidCount GetCentroidCount( const std::string & i_rCameraName ) const;
    // Output_GetCentroidPosition GetCentroidPosition( const std::string & i_rCameraName, const unsigned int i_CentroidIndex ) const;
    // Output_GetCentroidWeight GetCentroidWeight( const std::string & i_rCameraName, const unsigned int i_CentroidIndex ) const;
    // Output_GetGreyscaleBlobCount GetGreyscaleBlobCount( const std::string & i_rCameraName ) const;
    // Output_GetGreyscaleBlob GetGreyscaleBlob( const std::string & i_rCameraName, const unsigned int i_BlobIndex ) const;
    // Output_SetCameraFilter SetCameraFilter( const std::vector< unsigned int > & i_rCameraIdsForCentroids, const std::vector< unsigned int > & i_rCameraIdsForBlobs );

    //###################
    //Module initialisation
    //###################

    struct module_state
    {
        PyObject *error;
    };

    #define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

    //static PyObject * error_out(PyObject *m)
    //{
    //    struct module_state *st = GETSTATE(m);
    //    PyErr_SetString(st->error, "something bad happened");
    //    return NULL;
    //}

    //#####################
    // Methods
    //#####################
    static PyMethodDef PyviconMethods[] = {
         {"new_client", new_client, METH_VARARGS, "Create a Client instance"},
         {"pyvicon_version", pyvicon_version, METH_VARARGS, "Get SDK function"},
         {"pyvicon_connect", pyvicon_connect, METH_VARARGS, "Establish connection"},
         {"pyvicon_connect_to_multicast", pyvicon_connect_to_multicast, METH_VARARGS, "Establish a multicast connection"},
         {"pyvicon_disconnect", pyvicon_disconnect, METH_VARARGS, "Disconnect from connection"},
         {"pyvicon_isconnected", pyvicon_isconnected, METH_VARARGS, "Verify if connection is established"},
         {"pyvicon_start_transmitting_multicast", pyvicon_start_transmitting_multicast, METH_VARARGS, "Start multicast server transmission"},
         {"pyvicon_stop_transmitting_multicast", pyvicon_stop_transmitting_multicast, METH_VARARGS, "Stop multicast server transmission"},
         {"pyvicon_enable_segment_data", pyvicon_enable_segment_data, METH_VARARGS, ""},
         {"pyvicon_enable_marker_data", pyvicon_enable_marker_data, METH_VARARGS, ""},
         {"pyvicon_enable_unlabeled_marker_data", pyvicon_enable_unlabeled_marker_data, METH_VARARGS, ""},
         {"pyvicon_enable_device_data", pyvicon_enable_device_data, METH_VARARGS, ""},
         {"pyvicon_disable_segment_data", pyvicon_disable_segment_data, METH_VARARGS, ""},
         {"pyvicon_disable_marker_data", pyvicon_disable_marker_data, METH_VARARGS, ""},
         {"pyvicon_disable_unlabeled_marker_data", pyvicon_disable_unlabeled_marker_data, METH_VARARGS, ""},
         {"pyvicon_disable_device_data", pyvicon_disable_device_data, METH_VARARGS, ""},
         {"pyvicon_is_marker_data_enabled", pyvicon_is_marker_data_enabled, METH_VARARGS, ""},
         {"pyvicon_is_unlabeled_marker_data_enabled", pyvicon_is_unlabeled_marker_data_enabled, METH_VARARGS, ""},
         {"pyvicon_is_device_data_enabled", pyvicon_is_device_data_enabled, METH_VARARGS, ""},
         {"pyvicon_set_buffer_size", pyvicon_set_buffer_size, METH_VARARGS, "Set Frame buffer size"},
         {"pyvicon_set_stream_mode", pyvicon_set_stream_mode, METH_VARARGS, "Set client stream mode : ServerPush, ClientPull, ClientPullPreFetch"},
         {"pyvicon_set_axis_mapping", pyvicon_set_axis_mapping, METH_VARARGS, "Remaps the 3D axis"},
         {"pyvicon_get_axis_mapping", pyvicon_get_axis_mapping, METH_VARARGS, "Get the current Axis mapping"},
         {"pyvicon_get_frame", pyvicon_get_frame, METH_VARARGS, "Request a new frame to be fetched"},
         {"pyvicon_get_frame_number", pyvicon_get_frame_number, METH_VARARGS, "return the number of the last frame"},
         {"pyvicon_get_time_code", pyvicon_get_time_code, METH_VARARGS, "Return the timecode information for the last frame H,M,S"},
         {"pyvicon_get_frame_rate", pyvicon_get_frame_rate, METH_VARARGS, "Return the Vicon camera system frame rate in Hz at the time of the last frame retrieved"},
         {"pyvicon_get_latency_total", pyvicon_get_latency_total, METH_VARARGS, "Return total latency in the system"},
         {"pyvicon_get_subject_count", pyvicon_get_subject_count, METH_VARARGS, "Return the number of subjects in the Datastream"},
         {"pyvicon_get_subject_name", pyvicon_get_subject_name, METH_VARARGS, "Return the name of the subject"},
         {"pyvicon_get_subject_root_segment_name", pyvicon_get_subject_root_segment_name, METH_VARARGS, "Return root segment name"},
         {"pyvicon_get_segment_count", pyvicon_get_segment_count, METH_VARARGS, "Return the number of segments for a specified subject in the DataStream. This information can be used in conjunction with GetSegmentName."},
         {"pyvicon_get_segment_name", pyvicon_get_segment_name, METH_VARARGS, "Return the name of a subject segment specified by index."},
         {"pyvicon_get_segment_global_translation", pyvicon_get_segment_global_translation, METH_VARARGS, "Return segment global translation"},
         {"pyvicon_get_segment_global_rotation_matrix", pyvicon_get_segment_global_rotation_matrix, METH_VARARGS, "Return segment global rotation matrix"},
         {"pyvicon_get_segment_global_rotation_euler_xyz", pyvicon_get_segment_global_rotation_euler_xyz, METH_VARARGS, "Return segment global rotation Euler XYZ"},
         {"pyvicon_get_segment_global_rotation_helical", pyvicon_get_segment_global_rotation_helical, METH_VARARGS, "Return segment global rotation Helical"},
         {"pyvicon_get_segment_global_quaternion", pyvicon_get_segment_global_quaternion, METH_VARARGS, "Return segment global quaternion"},
         {"pyvicon_get_segment_local_translation", pyvicon_get_segment_local_translation, METH_VARARGS, "Return segment local translation"},
         {"pyvicon_get_segment_local_rotation_euler_xyz", pyvicon_get_segment_local_rotation_euler_xyz, METH_VARARGS, "Return the rotation of a subject segment in local Euler XYZ coordinates relative to its parent segment."},
         {"pyvicon_get_object_quality", pyvicon_get_object_quality, METH_VARARGS, "Return the quality score of a specified subject"},
         {"pyvicon_get_marker_count", pyvicon_get_marker_count, METH_VARARGS, "Return the number of markers for a specified subject"},
         {"pyvicon_get_marker_name", pyvicon_get_marker_name, METH_VARARGS, "Return the marker name"},
         {"pyvicon_get_marker_global_translation", pyvicon_get_marker_global_translation, METH_VARARGS, "return marker translation w.r.t global coordinate"},
         {"pyvicon_get_unlabeled_marker_count", pyvicon_get_unlabeled_marker_count, METH_VARARGS, "Return the number of unlabeled markers"},
         {"pyvicon_get_unlabeled_marker_global_translation", pyvicon_get_unlabeled_marker_global_translation, METH_VARARGS, "Return the position of unlabeled markers"},
         {"pyvicon_get_camera_count", pyvicon_get_camera_count, METH_VARARGS, "Get camera count"},
         {"pyvicon_get_camera_name", pyvicon_get_camera_name, METH_VARARGS, "Get camera name"},
         {NULL, NULL, 0, NULL}
    };

    static int pyvicon_traverse(PyObject *m, visitproc visit, void *arg)
    {
        Py_VISIT(GETSTATE(m)->error);
        return 0;
    }

    static int pyvicon_clear(PyObject *m)
    {
        Py_CLEAR(GETSTATE(m)->error);
        return 0;
    }

    /*
    static struct PyModuleDef moduledef =
    {
        PyModuleDef_HEAD_INIT,
        "pyvicon_module",
        NULL,
        sizeof(struct module_state),
        PyviconMethods,
        NULL,
        pyvicon_traverse,
        pyvicon_clear,
        NULL
    };
    #define INITERROR return NULL


    //########################
    // Module init function
    //########################
    PyMODINIT_FUNC PyInit_pyvicon_module(void) {
        PyObject *module = PyModule_Create(&moduledef);

        if (module == NULL)
        INITERROR;
        struct module_state *st = GETSTATE(module);

        st->error = PyErr_NewException("pyvicon_module.Error", NULL, NULL);
        if (st->error == NULL)
        {
            Py_DECREF(module);
            INITERROR;
        }
    return module;
    }
    */

    
    static struct PyModuleDef moduledef =
    {
        PyModuleDef_HEAD_INIT,
        "_pyvicon_datastream_wrapper",
        NULL,
        sizeof(struct module_state),
        PyviconMethods,
        NULL,
        pyvicon_traverse,
        pyvicon_clear,
        NULL
    };
    #define INITERROR return NULL


    //########################
    // Module init function
    //########################
    PyMODINIT_FUNC PyInit__pyvicon_datastream_wrapper(void) {
        PyObject *module = PyModule_Create(&moduledef);

        if (module == NULL)
        INITERROR;
        struct module_state *st = GETSTATE(module);

        st->error = PyErr_NewException("_pyvicon.Error", NULL, NULL);
        if (st->error == NULL)
        {
            Py_DECREF(module);
            INITERROR;
        }
    return module;
    }

#ifdef __cplusplus
} // end extern "C"
#endif // __cplusplus
