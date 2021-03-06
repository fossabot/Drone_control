#include "Remote.h"

void Remote::sendData(WebSocket<SERVER> *ws, float *values, float *time_pointer, OpCode opCode)
{
	// preparing results :
	char const *time_str = to_string(*time_pointer).c_str();
	char const *ang_0_str = to_string(values[0]).c_str();
	char const *ang_1_str = to_string(values[1]).c_str();
	char const *ang_2_str = to_string(values[2]).c_str();

	// sending data
	ws->send(ang_0_str, strlen(ang_0_str), opCode);
	ws->send(ang_1_str, strlen(ang_1_str), opCode);
	ws->send(ang_2_str, strlen(ang_2_str), opCode);
	ws->send(time_str, strlen(time_str), opCode);
}

void Remote::sendData(WebSocket<SERVER> *ws, int *values, float *time_pointer, OpCode opCode)
{
	// preparing results :
	char const *time_str = to_string(*time_pointer).c_str();
	char const *ang_0_str = to_string(values[0]).c_str();
	char const *ang_1_str = to_string(values[1]).c_str();
	char const *ang_2_str = to_string(values[2]).c_str();

	// sending data
	ws->send(ang_0_str, strlen(ang_0_str), opCode);
	ws->send(ang_1_str, strlen(ang_1_str), opCode);
	ws->send(ang_2_str, strlen(ang_2_str), opCode);
	ws->send(time_str, strlen(time_str), opCode);
}

void Remote::sendDataL(WebSocket<SERVER> *ws, Data *data, float *time_pointer, int length, OpCode opCode)
{
	// add params
	data->status[status_filter_mode] = data->parameters[params_IMU_Filter_mode];
	data->status[status_filter_param] = data->parameters[params_IMU_Filter_value];

	// preparing results :
	char const *time_str = to_string(*time_pointer).c_str();
	for (size_t i = 0; i < length; i++)
	{
		//cout << "i : " << i << " : " << data->status[i] << " ";
		char const *val = to_string(data->status[i]).c_str();
		// sending data
		ws->send(val, strlen(val), opCode);
	}
	ws->send(time_str, strlen(time_str), opCode);
}

void Remote::sendGains(WebSocket<SERVER> *ws, Data *data, float *time_pointer, int length, OpCode opCode)
{
	// preparing results :
	char const *time_str = to_string(*time_pointer).c_str();
	for (size_t i = 0; i < length; i++)
	{
		//cout << "i : " << i << " : " << data->controller_gains[i] << " ";
		char const *val = to_string(data->controller_gains[i]).c_str();
		// sending data
		ws->send(val, strlen(val), opCode);
	}
	ws->send(time_str, strlen(time_str), opCode);
}

void Remote::sendFStatus(WebSocket<SERVER> *ws, Data *data, float *time_pointer, OpCode opCode)
{
	/*
		0 : time
		1 : throttle
		2 : pitch
		3 : roll
		4 : yaw
		5 : gyr x
		6 : gyr y
		7 : gyr z
		8 : acc x
		9 : acc y
		10 : acc z
		11 : comp x
		12 : comp y
		13 : comp z
		14 : pid pitch
		15 : pid roll
		16 : pid yaw

		*/
	// preparing results :
	char const *time_str = to_string(*time_pointer).c_str();

	// command
	char const *commands_str_0 = to_string(data->commands[0]).c_str();
	char const *commands_str_1 = to_string(data->commands[1]).c_str();
	char const *commands_str_2 = to_string(data->commands[2]).c_str();
	char const *commands_str_3 = to_string(data->commands[3]).c_str();

	// gyr
	char const *gyr_str_0 = to_string(data->rates[0]).c_str();
	char const *gyr_str_1 = to_string(data->rates[1]).c_str();
	char const *gyr_str_2 = to_string(data->rates[2]).c_str();

	// gyr
	char const *acc_str_0 = to_string(data->acceleration[0]).c_str();
	char const *acc_str_1 = to_string(data->acceleration[1]).c_str();
	char const *acc_str_2 = to_string(data->acceleration[2]).c_str();

	// gyr
	char const *comp_str_0 = to_string(data->ang[0]).c_str();
	char const *comp_str_1 = to_string(data->ang[1]).c_str();
	char const *comp_str_2 = to_string(data->ang[2]).c_str(); // comp ang

	// pid
	char const *pid_str_0 = to_string(data->controller_gains[0]).c_str();
	char const *pid_str_1 = to_string(data->controller_gains[1]).c_str();
	char const *pid_str_2 = to_string(data->controller_gains[2]).c_str();

	// sending data
	ws->send(time_str, strlen(time_str), opCode); // time

	// commands
	ws->send(commands_str_0, strlen(commands_str_0), opCode);
	ws->send(commands_str_1, strlen(commands_str_1), opCode);
	ws->send(commands_str_2, strlen(commands_str_2), opCode);
	ws->send(commands_str_3, strlen(commands_str_3), opCode);

	// gyr
	ws->send(gyr_str_0, strlen(gyr_str_0), opCode);
	ws->send(gyr_str_1, strlen(gyr_str_1), opCode);
	ws->send(gyr_str_2, strlen(gyr_str_2), opCode);

	// acc
	ws->send(acc_str_0, strlen(acc_str_0), opCode);
	ws->send(acc_str_1, strlen(acc_str_1), opCode);
	ws->send(acc_str_2, strlen(acc_str_2), opCode);

	// comp
	ws->send(comp_str_0, strlen(comp_str_0), opCode);
	ws->send(comp_str_1, strlen(comp_str_1), opCode);
	ws->send(comp_str_2, strlen(comp_str_2), opCode);

	// comp
	ws->send(pid_str_0, strlen(pid_str_0), opCode);
	ws->send(pid_str_1, strlen(pid_str_1), opCode);
	ws->send(pid_str_2, strlen(pid_str_2), opCode);
}

std::vector<std::string> Remote::split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void Remote::start_remote(Data *data_i, float *time_now_in)
{
	static Data *data = data_i;
	static float *time_pointer = time_now_in;

	FileManagement::Log("REMOTE", "Started");
	Hub h;

	h.onMessage([](WebSocket<SERVER> *ws, char *message, size_t length, OpCode opCode) {
		if (opCode == OpCode::TEXT)
		{
			std::ostringstream os;
			for (size_t i = 0; i < length; i++)
			{
				os << message[i];
			}
			string r = string(os.str());

			std::vector<std::string> L_r = split(r, ' ');

			if (L_r.size() == 1)
			{
				if (L_r[0].compare("#ExpAbort") == 0)
				{
					data->status[status_experience_mode] = 0;
					FileManagement::Log("Remote", "Experience aborted");
					data->orders[0] = 0; // stop saving
					ws->send("OK", 2, opCode);
				}
				else if (L_r[0].compare("#ExpStart") == 0)
				{
					FileManagement::Log("Remote", "Experience started");
					data->status[status_experience_mode] = 1;
					ws->send("OK", 2, opCode);
				}

				else if (L_r[0].compare("#FStatus") == 0)
				{
					sendFStatus(ws, data, time_pointer, opCode);
				}
				else if (L_r[0].compare("#Status") == 0)
				{
					sendDataL(ws, data, time_pointer, status_length, opCode);
				}

				else if (r.compare("#OrdRecordOn") == 0)
				{
					// nothing
					std::cout << "OrdRecordOn\n";
					data->orders[0] = 1;
					ws->send("OK", 2, opCode);
				}
				else if (r.compare("#OrdRecordOff") == 0)
				{
					// nothing
					std::cout << "OrdRecordOff\n";
					data->orders[0] = 0;
					ws->send("OK", 2, opCode);
				}

				// DK : display gains
				else if (r.compare("#OrdDKOn") == 0)
				{
					// nothing
					data->orders[1] = 1;
					ws->send("OK", 2, opCode);
				}
				else if (r.compare("#OrdDKOff") == 0)
				{
					// nothing
					data->orders[orders_DisplayGains] = 0;
					ws->send("OK", 2, opCode);
				}

				// File Management :
				else if (r.compare("#FL") == 0)
				{ // FL : FileList
					std::string strlist = FileManagement::listDir("/home/pi/log");
					char const *data = strlist.c_str();
					ws->send(data, strlen(data), opCode);
				}

				else if (r.compare("#FS") == 0)
				{ // FL : FileSend
				}

				else if (r.compare("#AngComp") == 0)
				{
					sendData(ws, data->ang, time_pointer, opCode);
				}

				else if (r.compare("#PIDErrP") == 0)
				{
					sendData(ws, data->pid_debug, time_pointer, opCode);
				}
				else if (r.compare("#PID") == 0)
				{
					sendData(ws, data->pid_out, time_pointer, opCode);
				}

				else if (r.compare("#Acc") == 0)
				{
					sendData(ws, data->acceleration, time_pointer, opCode);
				}
				else if (r.compare("#Gyr") == 0)
				{
					sendData(ws, data->rates, time_pointer, opCode);
				}

				else if (r.compare("#ListFiles") == 0)
				{
					// nothing
					std::cout << "#ListFiles\n";
				}
				else if (L_r[0].compare("#GetGainsRate") == 0)
				{
					sendGains(ws, data, time_pointer, gains_length, opCode);
				}
				else
				{
					FileManagement::Log("Remote", "command unknown : |" + r + "|");
					ws->send("KO", 2, opCode);
				}
			}
			else if (L_r.size() > 1)
			{

				if (L_r[0].compare("#setFilter") == 0)
				{ // set filter
					if (L_r[1].compare("NONE") == 0)
					{
						data->stabilisation_mode = IMU_Filter_usage_none;
						data->status[status_filter_mode] = IMU_Filter_usage_none;
						FileManagement::Log("Remote", "Filter mode none");
						ws->send("OK", 2, opCode);
					}
					else if (L_r[1].compare("ACC") == 0)
					{
						data->stabilisation_mode = IMU_Filter_usage_acc;
						data->status[status_filter_mode] = IMU_Filter_usage_acc;
						FileManagement::Log("Remote", "Filter mode acc");
						ws->send("OK", 2, opCode);
					}
					else if (L_r[1].compare("GYR") == 0)
					{
						data->stabilisation_mode = IMU_Filter_usage_gyr;
						data->status[status_filter_mode] = IMU_Filter_usage_gyr;
						FileManagement::Log("Remote", "Filter mode gyr");
						ws->send("OK", 2, opCode);
					}
					else if (L_r[1].compare("BOTH") == 0)
					{
						data->stabilisation_mode = IMU_Filter_usage_both;
						data->status[status_filter_mode] = IMU_Filter_usage_both;
						FileManagement::Log("Remote", "Filter both");
						ws->send("OK", 2, opCode);
					}
					else
					{
						FileManagement::Log("Remote", "setFilter : parameter unknown : |" + L_r[0] + "|" + L_r[1] + "|");
						ws->send("KO", 2, opCode);
					}

					FileManagement::saveDataSettings(*data);
				}
				else if (L_r[0].compare("#OrdRecord") == 0)
				{
					if (L_r[1].compare("OFF") == 0)
					{
						// nothing
						std::cout << "OrdRecordOff\n";
						data->orders[0] = 0;
						ws->send("OK", 2, opCode);
					}
					else if (L_r[1].compare("ON") == 0)
					{
						// nothing
						std::cout << "OrdRecordOn\n";
						data->orders[0] = 1;
						ws->send("OK", 2, opCode);
					}
				}
				else if (L_r[0].compare("#SetFilterMode") == 0)
				{
					// set values
					data->parameters[params_IMU_Filter_mode] = std::stof(L_r[1]);
					FileManagement::Log("Remote", "Set filer mode " + std::to_string(data->parameters[params_IMU_Filter_mode]) + " ");

					// save gains
					FileManagement::saveDataSettings(*data);

					ws->send("OK", 2, opCode);
				}
				else if (L_r[0].compare("#SetFilterValue") == 0)
				{
					// set values
					data->parameters[params_IMU_Filter_value] = std::stof(L_r[1]);
					FileManagement::Log("Remote", "Set filer value " + std::to_string(data->parameters[params_IMU_Filter_value]) + " ");

					// save gains
					FileManagement::saveDataSettings(*data);

					ws->send("OK", 2, opCode);
				}

				// gains
				else if (L_r[0].compare("#SetGainsRate") == 0)
				{
					int index = std::stoi(L_r[1]);
					// set values
					if (index < gains_length)
					{
						data->controller_gains[index] = std::stof(L_r[2]);

						FileManagement::Log("Remote", "Set gains " + std::to_string(data->controller_gains[index]) + " ");
						// save gains
						FileManagement::saveDataSettings(*data);

						ws->send("OK", 2, opCode);
					}
					else
					{
						cout << "[ Remote ] : gived an index out of array range";
						ws->send("KO", 2, opCode);
					}
				}

				else
				{
					FileManagement::Log("Remote", "command unknown : |" + L_r[0] + "|" + L_r[1] + "|");
					ws->send("KO", 2, opCode);
				}
			}
			else
			{
				FileManagement::Log("Remote", "command unknown : |" + r + "|");
				cout << "L_r size : " << L_r.size() << "\n";
				ws->send("KO", 2, opCode);
			}
		}
	});

	if (h.listen(8766))
	{
		h.run();
		FileManagement::Log("Remote", "Started");
	}
	pthread_exit(NULL);
}

void Remote::launch(Data *data_in, float *time_now)
{
	first = std::thread(start_remote, data_in, time_now);
}
