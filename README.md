# Automatic-Interface-Testing-for-System-Call-Interception-Frameworks
The system call interface is the central mechanism for userspace programs to interact across their operating system enforce process isolation. It provides the services of the operating system to the user programs via Application Program Interface(API). It provides an interface between a process and operating system to allow user-level processes to request services of the operating system. System calls are the only entry points into the kernel system. System Call Interceptors interpose the interaction between the program and the operating system to inspect a program's behavior or modify the interaction. The SCONE Shielding Layer is an example of the latter.

SCONE enables the transparent execution of legacy software in Intel SGX enclaves. While SGX protects the program's memory content and execution from eavesdropping and malicious modifications, the interaction with the operating system, which is necessary for all non-trivial applications, would easily be observable and could further be used by an adversary to tamper with the program's execution rendering the SGX protection hollow. SCONE's Shielding Layer solves this issue by transparently protecting, for example through encryption, the program data before giving the system call to the operating system. To achieve its security guarantees, a correct implementation of the shielding layer is vital. Unfortunately, the processed system calls are too involved in number and structure for an exhaustive manual testing process.

The goal of this work is to create an automatic testing framework for system call interceptors. For this means, a model of the system call interface's calls, their arguments and responses has to be designed and implemented in Rust. This model realizes three functions:

+ Generating valid system calls. This function enables the model to generate valid systems calls.

+ Parsing. This function enables the model to tell if a system call response is valid corresponds to a system call when a pair of system call and system call response is given.

(Q: Does it mean that the model checks the response according to how the reterned arguments are difined for certain system call?)

+ Generating valid system call responses. This function enable the model to generate a valid system call when a system call is given. <s>This function can behave benign or malicious depands on the need. While a benign model generates valid reponses the same as the kernal system, a malicious model may only generate 'valid' reponse from the point of view of format. That is to say, the content of a malicious response doesn't contain valid information, although it is delivered in standard format.</s>

(Q: Does it mean that the model itself has the ability to response a system call without the attendance of the kernel side? Or just collect the response after generating the system call?)


Two implimentations are inspired from the model.

+ First, the model should empower us to fuzz test the system call interceptor from the application, as well as, the kernel side by generating random, but well-structured system calls (requests) respectively system call responses. In our case, an application based on this model is under the protection of the SCONE Shielding Layer. The application generates system calls and these system calls are deliverd to the kernel side through the SCONE Shielding Layer. The responses will be recorded and compired with the responses where the input is the same but SCONE Shielding Layer is absent.

+ Moreover, allow us to ensure the integrity of any given system call request/response, e.g., that arguments have the expected data type or that given (array/buffer) size arguments are correct. 
(Q: Does it mean that the model first track the system call and check if the response is valid in advance?)

The effectiveness of the approach shall be evaluated by comparing the responses of an intercepted system call interface to a not intercepted baseline using fuzz tests.
