class Data
{
  private:
    /* data */
  public:
    Data(/* args */);

    float t = 0; // time
    float ang[3] = {0, 0, 0};
    float ang_acc[3] = {0, 0, 0};

    float acceleration[3] = {0, 0, 0};
    float rates[3] = {0, 0, 0};

    int commands[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float commands_gen[4] = {0, 0, 0, 0}; // to have an idea of what commands we send to the control algorithm, in ° or in °/s

    // remote
    int pid_out[3] = {0, 0, 0};
    float pid_debug[3] = {0, 0, 0};

    float motors[4] = {0, 0, 0, 0};
    int motors_output[4] = {0, 0, 0, 0};
    int sensors[2] = {0, 0}; // pressure, temperature
    int frequency_crtl[2] = {0, 0};

    // safety
    bool flag_error = false;
    bool flag_not_ready = true; // boot with this flag enabled

    bool isArmed = false;
    bool isArming = false;
    int stabilisation_mode = 0; // rates = 0, angle = 1
        //float cmd[3] = {0, 0, 0};   // command mapped

    // saving

    int orders[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double status[status_length];

    // adding a status save system : ease dvpt
    int f_display_iterationscount = 6000;

    ~Data();
};

Data::Data(/* args */)
{
    FileManagement::Log("DATA", "Initialised");
}

Data::~Data()
{
}
