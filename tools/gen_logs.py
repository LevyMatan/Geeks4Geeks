'''
gen_logs generates random log entries and writes them to a file.
It is to test the logger.
'''
import time
import random

LOG_FILE = 'log.txt'
log_levels = ['INFO', 'WARNING', 'ERROR']
log_messages = ['Something happened', 'Something went wrong', 'Something broke']
log_origin = ['main', 'logger', 'tools']

while True:
    # Generate random log entry
    timestamp = time.strftime('%Y-%m-%d %H:%M:%S.') + str(random.randint(0, 999)).zfill(3)
    level = random.choice(log_levels)
    message = random.choice(log_messages)
    origin = random.choice(log_origin)
    line_number = random.randint(0, 1000)
    log_entry = f'{timestamp}|{origin}|{line_number}|{level}|{message}\n'

    # Write log entry to file
    with open(LOG_FILE, 'a', encoding='utf-8' ) as f:
        f.write(log_entry)

    # Wait for random amount of time before generating next log entry
    time.sleep(random.uniform(0.001, 0.10))
