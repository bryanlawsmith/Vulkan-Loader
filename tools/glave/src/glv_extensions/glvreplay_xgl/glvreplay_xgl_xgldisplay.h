/*
 * Vulkan
 *
 * Copyright (C) 2014 LunarG, Inc.
 * Copyright (C) 2015 Valve Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "glvreplay_xgl_xglreplay.h"

class xglDisplay: public glv_replay::DisplayImp {
friend class xglReplay;
public:
    xglDisplay();
    ~xglDisplay();
    int init(const unsigned int gpu_idx);
    int set_window(glv_window_handle hWindow, unsigned int width, unsigned int height);
    int create_window(const unsigned int width, const unsigned int height);
    void resize_window(const unsigned int width, const unsigned int height);
    void process_event();
    // XGL_DEVICE get_device() { return m_dev[m_gpuIdx];}
#if defined(PLATFORM_LINUX) || defined(XCB_NVIDIA)
    xcb_window_t get_window_handle() { return m_XcbWindow; }
#elif defined(WIN32)
    HWND get_window_handle() { return m_windowHandle; }
#endif
private:
    XGL_RESULT init_xgl(const unsigned int gpu_idx);
    bool m_initedXGL;
#if defined(PLATFORM_LINUX) || defined(XCB_NVIDIA)
    XGL_WSI_X11_CONNECTION_INFO m_WsiConnection;
    xcb_screen_t *m_pXcbScreen;
    xcb_window_t m_XcbWindow;
#elif defined(WIN32)
    HWND m_windowHandle;
#endif
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    unsigned int m_frameNumber;
    std::vector<uint32_t> imageWidth;
    std::vector<uint32_t> imageHeight;
    std::vector<XGL_IMAGE> imageHandles;
    std::vector<XGL_GPU_MEMORY> imageMemory;
#if 0
    XGL_DEVICE m_dev[XGL_MAX_PHYSICAL_GPUS];
    uint32_t m_gpuCount;
    unsigned int m_gpuIdx;
    XGL_PHYSICAL_GPU m_gpus[XGL_MAX_PHYSICAL_GPUS];
    XGL_PHYSICAL_GPU_PROPERTIES m_gpuProps[XGL_MAX_PHYSICAL_GPUS];
#endif
    std::vector<char *>m_extensions;
};
