/* Copyright 2015-present Samsung Electronics Co., Ltd. and other contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IOTJS_ENV_H
#define IOTJS_ENV_H

#include "iotjs_list.h"
#include "uv.h"

typedef struct {
  bool wait_source;
  bool context_reset;
  int port;
} DebuggerConfig;

typedef struct {
  bool loadstat;
  bool memstat;
  bool show_opcode;
  DebuggerConfig* debugger;
} Config;

typedef enum {
  kInitializing,
  kRunningMain,
  kRunningLoop,
  kExiting,
} State;

typedef struct {
  // Number of application arguments including 'iotjs' and app name.
  uint32_t argc;

  // Application arguments list including 'iotjs' and app name.
  char** argv;

  // I/O event loop.
  uv_loop_t* loop;
  uv_idle_t* immediate_idle_handle;
  uv_check_t* immediate_check_handle;

  // store all handlewrap objects
  list_t* handlewrap_queue;

  // Running state.
  State state;

  // Run config
  Config config;

} IOTJS_VALIDATED_STRUCT(iotjs_environment_t);


iotjs_environment_t* iotjs_environment_get();
void iotjs_environment_release();

bool iotjs_environment_parse_command_line_arguments(iotjs_environment_t* env,
                                                    uint32_t argc, char** argv);

uint32_t iotjs_environment_argc(const iotjs_environment_t* env);
const char* iotjs_environment_argv(const iotjs_environment_t* env,
                                   uint32_t idx);

uv_loop_t* iotjs_environment_loop(const iotjs_environment_t* env);
void iotjs_environment_set_loop(iotjs_environment_t* env, uv_loop_t* loop);

const Config* iotjs_environment_config(const iotjs_environment_t* env);
const DebuggerConfig* iotjs_environment_dconfig(const iotjs_environment_t* env);

void iotjs_environment_create_handlewrap(void* handlewrap);
void iotjs_environment_remove_handlewrap(void* handlewrap);
void iotjs_environment_cleanup_handlewrap();

void iotjs_environment_go_state_running_main(iotjs_environment_t* env);
void iotjs_environment_go_state_running_loop(iotjs_environment_t* env);
void iotjs_environment_go_state_exiting(iotjs_environment_t* env);
bool iotjs_environment_is_exiting(iotjs_environment_t* env);

#endif /* IOTJS_ENV_H */
