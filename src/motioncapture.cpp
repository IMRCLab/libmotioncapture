#include "libmotioncapture/motioncapture.h"
#ifdef ENABLE_VICON
#include "libmotioncapture/vicon.h"
#endif
#ifdef ENABLE_QUALISYS
#include "libmotioncapture/qualisys.h"
#endif
#ifdef ENABLE_NOKOV
#include "libmotioncapture/nokov.h"
#endif
#ifdef ENABLE_VRPN
#include "libmotioncapture/vrpn.h"
#endif

namespace libmotioncapture {

  const char *version_string =
    #include "../version"
    ;

  const char *version()
  {
    return version_string;
  }

  RigidBody MotionCapture::rigidBodyByName(
      const std::string& name) const
  {
    const auto& obj = rigidBodies();
    const auto iter = obj.find(name);
    if (iter != obj.end()) {
      return iter->second;
    }
    throw std::runtime_error("Rigid body not found!");
  }

  std::string getString(
    const std::map<std::string, std::string> &cfg,
    const std::string& key,
    const std::string& default_value)
  {
    const auto iter = cfg.find(key);
    if (iter != cfg.end()) {
      return iter->second;
    }
    return default_value;
  }

  bool getBool(
    const std::map<std::string, std::string> &cfg,
    const std::string& key,
    bool default_value)
  {
    const auto iter = cfg.find(key);
    if (iter != cfg.end()) {
      if (iter->second == "1" || iter->second == "true") {
        return true;
      }
      return false;
    }
    return default_value;
  }

  int getInt(
      const std::map<std::string, std::string> &cfg,
      const std::string &key,
      int default_value)
  {
    const auto iter = cfg.find(key);
    if (iter != cfg.end())
    {
      return std::stoi(iter->second);
    }
    return default_value;
  }

  MotionCapture *MotionCapture::connect(
      const std::string &type,
      const std::map<std::string, std::string> &cfg)
  {
    MotionCapture* mocap = nullptr;

    if (false)
    {
    }
#ifdef ENABLE_VICON
    else if (type == "vicon")
    {
      mocap = new libmotioncapture::MotionCaptureVicon(
        getString(cfg, "hostname", "localhost"),
        getBool(cfg, "enable_objects", true),
        getBool(cfg, "enable_pointclout", true));
    }
#endif
#ifdef ENABLE_QUALISYS
    else if (type == "qualisys")
    {
      mocap = new libmotioncapture::MotionCaptureQualisys(
        getString(cfg, "hostname", "localhost"),
        getInt(cfg, "port", 22222),
        getBool(cfg, "enable_objects", true),
        getBool(cfg, "enable_pointclout", true));
    }
#endif
#ifdef ENABLE_NOKOV
	else if (type == "nokov")
	{
        mocap = new libmotioncapture::MotionCaptureNokov(
            getString(cfg, "hostname", "localhost"),
            getBool(cfg, "enableFrequency", false),
            getInt(cfg, "updateFrequency", 100));
  }
#endif
#ifdef ENABLE_VRPN
    else if (type == "vrpn")
    {
      mocap = new libmotioncapture::MotionCaptureVrpn(
        getString(cfg, "hostname", "localhost"));
    }
#endif
    else
    {
      throw std::runtime_error("Unknown motion capture type!");
    }

    return mocap;
  }

}
