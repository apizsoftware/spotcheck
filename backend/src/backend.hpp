#pragma once

#include "analyze.hpp"
#include "make_cv_roi.hpp"
#include "async.hpp"
#include "parse_gal.hpp"
#include "spot.hpp"
#include "test_thresh.hpp"
#include "preview_normalized.hpp"

#include <array>
#include <random>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <node.h>
#include <node_object_wrap.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <utility>
#include <v8.h>

class backend : public node::ObjectWrap {
public:
    static void init(v8::Local<v8::Object> exports,
                     v8::Local<v8::Object> module);

private:
    using callback_info = v8::FunctionCallbackInfo<v8::Value>;
    static v8::Persistent<v8::Function> constructor;
    static void alloc(const callback_info & args);
    static void import_source_image(const callback_info & args);
    static void import_source_gal(const callback_info & args);
    static void split_sectors(const callback_info & args);
    static void clear_targets(const callback_info & args);
    [[deprecated]] static void test_thresh(const callback_info & args);
    static void add_target(const callback_info & args);
    static void provide_norm_preview(const callback_info & args);
    static void is_busy(const callback_info & args);
    static cv::Mat m_source_image;
    struct Target {
	int64_t rowId, colId;
	double fractStartx, fractStarty;
        double fractEndx, fractEndy;
        int64_t threshold;
    };
    static std::vector<Target> m_targets;
};
