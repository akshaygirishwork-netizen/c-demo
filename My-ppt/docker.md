
A container is like a lightweight virtual environment that shares the host OS kernel but keeps the application isolated from other processes.
You define how your app runs using a Dockerfile, which builds a Docker image.
That image can then be run anywhere as a container, behaving the same way every time.

🌟 Advantages of Docker Over Host Application
Advantage	Explanation
1. Isolation	Each app runs in its own container, so it doesn’t interfere with others or the host system.
2. Portability	Containers run the same across all environments — no “it works on my machine” issues.
3. Easy Deployment	You can quickly deploy or roll back apps just by starting/stopping containers.
4. Consistency	The same Docker image can be used for development, testing, and production.
5. Lightweight	Containers share the host OS kernel, so they use less memory and start faster than virtual machines.
6. Simplified Updates	You can update or replace individual containers without affecting the entire system.
7. Version Control	Each image version can be tracked, tagged, and rolled back easily.