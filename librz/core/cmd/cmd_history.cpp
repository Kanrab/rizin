// SPDX-FileCopyrightText: 2021 RizinOrg <info@rizin.re>
// SPDX-FileCopyrightText: 2021 deroad <wargio@libero.it>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_util/rz_path.hpp>
#include <rz_core.hpp>
#include <rz_cmd.hpp>
#include <rz_cons.hpp>

RZ_IPI RzCmdStatus rz_history_list_or_exec_handler(RzCore *core, int argc, const char **argv) {
	if (argc == 1) {
		rz_line_hist_list(core->cons->line);
		return RZ_CMD_STATUS_OK;
	}

	int index = atoi(argv[1]);
	if (index < 1) {
		RZ_LOG_ERROR("index must be a positive number.\n");
		return RZ_CMD_STATUS_ERROR;
	}

	const char *cmd = rz_line_hist_get(core->cons->line, index);
	if (!cmd) {
		RZ_LOG_ERROR("cannot find command with index %d.\n", index);
		return RZ_CMD_STATUS_ERROR;
	}

	int ret = rz_core_cmd0(core, cmd);
	return !ret ? RZ_CMD_STATUS_OK : RZ_CMD_STATUS_ERROR;
}

RZ_IPI RzCmdStatus rz_history_clear_handler(RzCore *core, int argc, const char **argv) {
	rz_line_hist_free(core->cons->line);
	return RZ_CMD_STATUS_OK;
}

RZ_IPI RzCmdStatus rz_history_save_handler(RzCore *core, int argc, const char **argv) {
	char *history = rz_path_home_history();
	rz_line_hist_save(core->cons->line, history);
	free(history);
	return RZ_CMD_STATUS_OK;
}
