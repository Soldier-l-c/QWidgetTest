#pragma once
#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <filesystem>
#include <shared_mutex>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QTimer>

#include <Qt/include/BaseWindow.h>
#include <Qt/include/helper/i18n_loader_helper.h>
#include <Qt/include/helper/qt_util_helper.h>

#include <helper/util_time.h>
#include <helper/util_path.h>
#include <helper/util_rapidjson.h>
#include <helper/util_string.h>
#include <thread/thread_pool.h>

#include "public/result_code.h"
#include <interface/smart_base.h>
#include <interface/smart_object.h>
#include <interface/object_creater.h>
#include <logger/ILogger.h>
#include <base/INetHelper.h>
#include <base/NetHelper.h>

#include <base/ITimer.h>

extern ILoggerPtr g_logger;
#define LOG ILOG

#define VERF_PTR(ptr, ret)if(!ptr){LOG(ERROR)<<__FILE__<<":"<<__LINE__<<"INVALID Ptr!";return ret;}