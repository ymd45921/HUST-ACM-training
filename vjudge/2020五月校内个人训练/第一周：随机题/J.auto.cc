/**
 *
 */
#include <iostream>
#include <sys/stat.h>
#include <functional>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

using namespace std;
using longs = long long;
using func = function<void*(void*)>;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

struct fifoInfo {const char *j2u, *u2j;};
const char j2u[] = "j2u.fifo";
const char u2j[] = "u2j.fifo";
const char judge_path[] = "/mnt/c/Users/shiroha/Desktop/judge.bin";
const char user_path[] = "/mnt/c/Users/shiroha/Desktop/user.bin";
const char judge_arg[] = "/mnt/c/Users/shiroha/Desktop/xxx.txt";

int forkChild(int &pid, const func &process,
              void *param = nullptr, void **ret = nullptr)
{
    pid = fork();
    if (pid < 0) return 1;
    else if (pid == 0) process(param);
    return 0;
}

func judge = [](void *param) -> void*
{
    auto para = (fifoInfo *) param;
    int in = open(para->u2j, O_RDONLY);
    int out = open(para->j2u, O_WRONLY);

    dup2(in, 0); dup2(out, 1);
    close(in); close(out);

    execl(judge_path, "judge" ,judge_arg, nullptr);
    return nullptr;
};

func user = [](void *param) -> void*
{
    auto para = (fifoInfo *) param;
    int out = open(para->u2j, O_WRONLY);
    int in = open(para->j2u, O_RDONLY);

    dup2(in, 0); dup2(out, 1);
    close(in); close(out);

    execl(user_path, "user", nullptr);
    return nullptr;
};

void result(int argc, const int argv[])
{
    cerr << "Process completed." << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fifoInfo pip {j2u, u2j};
    mkfifo(j2u, 0644);
    mkfifo(u2j, 0644);

    pid_t pid[2];
    auto x1 = forkChild(pid[0], judge, &pip);
    auto x2 = forkChild(pid[1], user, &pip);
    if (x1 || x2)
    {
        cerr << "Fork process failed ..." << endl;
        exit(EXIT_FAILURE);
    }

    int ret[2];
    waitpid(pid[0], &ret[0], 0);
    waitpid(pid[1], &ret[1], 0);
    result(2, ret);

    return 0;
}