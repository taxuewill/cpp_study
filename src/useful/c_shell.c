FILE *fstream = NULL;
    char buff[4096];
    memset(buff, 0, sizeof(buff));
    if (NULL == (fstream = popen("ps -e -T -o NAME -o -TID -o CMD -o SCHED|grep com.will.test.threadsched", "r")))
    {
        fprintf(stderr, "execute command failed: %s", strerror(errno));
        return false;
    }

    while (NULL != fgets(buff, sizeof(buff), fstream))
    {
        printf("-----");
        int pid = -1;
        string threadInfo = string(buff);
        printf("%s", threadInfo.c_str());
    }
    pclose(fstream);
    //     bool findPid = false;
    //     int position = 0;
    //     if (threadInfo.empty())
    //     {
    //         continue;
    //     }

    //     threadInfo.erase(0, threadInfo.find_first_not_of(" "));
    //     threadInfo.erase(threadInfo.find_last_not_of(" ") + 1);
    //     string pidStr = threadInfo.substr(0, threadInfo.find_first_of(" "));

    //     printf("pidStr is %s\n", pidStr.c_str());
    //     pid = atoi(pidStr.c_str());

    //     printf("pid is %d\n", pid);

    //     pclose(fstream);
    //     if (pid > 0)
    //     {
    //         ostringstream ostrCmd;
    //         ostrCmd << "chrt -p " << pid << " -r 99" << endl;
    //         printf("to exec %s\n", ostrCmd.str().c_str());
    //         system(ostrCmd.str().c_str());
    //     }
    // }
/////////###########################################
FILE * stream;
const int max_buffer = 256;
        char buffer[max_buffer];
        cmd.append(" 2>&1");
        stream = popen(cmd.c_str(), "r");
        if (stream) {
            while (!feof(stream))
                if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);

            pclose(stream);

        }
    