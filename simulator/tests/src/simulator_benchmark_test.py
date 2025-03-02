import glob
import os
import platform
import psutil
import subprocess
import time

ALGORITHMS = ["KMP", "brute-force", "Rabin-Karp", "Z-algorithm", "shift-or", "Aho-Corasick", "suffix-tree", "boyer-moore"]


def run_simulator(algorithm_name, text_path, substring_path):
    simulator_base = ["simulator", "bin", "run-simulator"]

    if platform.system() == "Windows":
        simulator_base = ["simulator", "bin", "Release", "run-simulator.exe"]

    simulator_path = os.path.join(*simulator_base)

    command = [simulator_path, "--algorithm", algorithm_name, "-T", text_path, "-S", substring_path]

    if not os.path.exists(simulator_path):
        print(f"Simulator executable not found: {simulator_path}")
        return

    try:
        process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        memory_used = 0

        # Monitor memory usage
        while process.poll() is None:
            mem_info = psutil.Process(process.pid).memory_info()
            current_memory = mem_info.rss / (1024 * 1024)  # Convert to MB
            if current_memory > memory_used:
                memory_used = current_memory
            time.sleep(0.01)

        stdout, stderr = process.communicate()

        if stderr:
            print(f"Error while executing algorithm {algorithm_name}: {stderr.decode()}")
            return

        print(f"Results for algorithm {algorithm_name}:\n{stdout.decode()}")
        print(f"Peak memory usage: {memory_used:.2f} MB\n-----------------------------------\n\n")

    except Exception as e:
        print(f"An error occurred while running algorithm {algorithm_name}: {e}")


def main():
    test_base_path = os.path.join("simulator", "tests", "resources")
    test_directories = [d for d in glob.glob(os.path.join(test_base_path, "test-*")) if os.path.isdir(d)]

    for test_dir in test_directories:
        text_path = os.path.join(test_dir, "text.txt")
        substring_path = os.path.join(test_dir, "substring.txt")

        if os.path.exists(text_path) and os.path.exists(substring_path):
            for alg in ALGORITHMS:
                print(f"Running simulator for algorithm: {alg}, directory: {test_dir}")
                run_simulator(alg, text_path, substring_path)
                time.sleep(1)
        else:
            print(f"text.txt or substring.txt not found in directory {test_dir}")


if __name__ == "__main__":
    main()
