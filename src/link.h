/*
 * link.h — 和 Ecam 的 UART 链路
 *
 * 协议见 Ecam 仓库 README 的"外接模块 → 履带车"一节（两边必须一致）：
 *
 *   Ecam → C2   x<f> y<f>\n          差速控制，x 转向、y 前后，各 -1..1
 *   Ecam → C2   #hi                  问身份
 *   C2 → Ecam   #ok v1 tank          应答
 *   Ecam → C2   #wifi 1 <b64 SSID>
 *   Ecam → C2   #wifi 2 <b64 PASS>
 *   Ecam → C2   #wifi 3              到这一行才真的存 NVS 并连
 *   C2 → Ecam   #wifi ok | #wifi err <code>
 *   C2 → Ecam   #ip <addr>           拿到 IP / 掉线（空地址）
 *
 * **运动指令 500ms 不来就自动停车**（和参考项目的看门狗同长）。
 */
#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 建 UART + 起解析任务。重复调用是空操作 */
esp_err_t link_start(void);

/* 主动往 Ecam 报一次 IP（wifi_prov 的回调会调它，web.c 那侧不用管） */
void link_send_ip(const char *ip);

#ifdef __cplusplus
}
#endif
