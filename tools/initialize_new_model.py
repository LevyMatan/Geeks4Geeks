'''
initialize_new_model.py
-----------------------
This script is used to initialize a new model. It will create the necessary
directories and files for the model to run. It will also create a new
configuration file for the model. The user will be prompted to enter the
necessary information for the model to run.

project tree view:
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── VERSION
├── all
│   ├── CMakeLists.txt
│   └── VERSION
├── cmake
│   ├── CPM.cmake
│   ├── GetVersionFromGitTag.cmake
│   └── tools.cmake
├── codecov.yaml
├── documentation
│   ├── CMakeLists.txt
│   ├── Doxyfile
│   ├── conf.py
│   └── pages
│       └── about.dox
├── include
│   ├── add_binary_strings
│   │   └── add_binary_strings.h
│   ├── binary_tree_from_string_with_bracket_representation
│   │   └── binary_tree_from_string_with_bracket_representation.h
│   ├── flip_bits
│   │   └── flip_bits.h
│   ├── full_binary_trees
│   │   └── full_binary_trees.h
│   ├── greeter
│   │   └── greeter.h
│   ├── maximum_sub_array
│   │   └── maximum_sub_array.h
│   ├── shenyrash_and_his_bits
│   │   └── shenyrash_and_his_bits.h
│   ├── shortest_path_by_removing_k
│   │   └── shortest_path_by_removing_k.h
│   └── utils
│       └── debug.h
├── source
│   ├── add_binary_strings.cpp
│   ├── binary_tree_from_string_with_bracket_representation.cpp
│   ├── flip_bits.cpp
│   ├── full_binary_trees.cpp
│   ├── greeter.cpp
│   ├── maximum_sub_array.cpp
│   ├── shenyrash_and_his_bits.cpp
│   └── shortest_path_by_removing_k.cpp
├── standalone
│   ├── CMakeLists.txt
│   ├── VERSION
│   └── source
│       └── main.cpp
├── test
│   ├── CMakeLists.txt
│   ├── VERSION
│   └── source
│       ├── add_binary_strings.cpp
│       ├── binary_tree_from_string_with_bracket_representation.cpp
│       ├── flip_bits.cpp
│       ├── full_binary_trees.cpp
│       ├── greeter.cpp
│       ├── main.cpp
│       ├── maximum_sub_array.cpp
│       ├── shenyrash_and_his_bits.cpp
│       ├── shortest_path_by_removing_k.cpp
│       └── shortest_path_by_removing_k_tc.txt
└── tools
    └── initialize_new_model.py

    Idea:
    When create a new module, the following steps should be coverd:
    1. Create a new directory for the module in the include directory.
       In the folder, create a header file with the same name as the module.
       The header file should have a header description string like:
            #pragma once
            /**
            * @file maximum_sub_array.h
            * @author Matan Levy (levymatanlevy@gmail.com)
            * @brief
            * @version 0.1
            * @date 2022-11-27
            *
            * @copyright Copyright (c) 2022
            *
            */
    2. Create a new source file with the module name under the source directory.
       The source file should have a file description string like:
            /**
            * @file maximum_sub_array.cpp
            * @author Matan Levy (levymatanlevy@gmail.com)
            * @brief
            * @version 0.1
            * @date 2022-11-27
            *
            */
        The source file should include the header file of the module.
    3. Create a new test file with the module name under the test/source directory.
       The test file should include the header file of the module.
       and the header file of the test framework.
       #include <doctest/doctest.h>

'''

import sys
import os
import datetime


def make_directories(module_name):
    '''
    Creates a directory for the module if it does not already exist.
    '''

    #checko if the module directory exists in the include directory
    module_name = '../include/' + module_name
    if not os.path.exists(module_name):
        os.makedirs(module_name)
    else:
        print('The module directory already exists.')


def create_header_file(module_name):
    '''
    Creates a header file for the module if it does not already exist.
    '''

    #check if the header file exists in the module directory
    header_file_name = '../include/' + module_name + '/' + module_name + '.h'
    if not os.path.exists(header_file_name):
        with open(header_file_name, 'w+', encoding='utf-8') as header_file:
            header_file.write('#pragma once\n')
            header_file.write('/**\n')
            header_file.write('* @file ' + module_name + '.h\n')
            header_file.write('* @author Matan Levy (levymatanlevy@gmail.com)\n')
            header_file.write('* @brief\n')
            header_file.write('* @version 0.1\n')
            todays_date_string = datetime.date.today().strftime('%Y-%m-%d')
            header_file.write(f'* @date {todays_date_string}\n')
            header_file.write('*\n')
            header_file.write('*\n')
            header_file.write('*/\n')
    else:
        print('The header file already exists.')

def create_md_file(module_name):
    '''
    Creates a MarkDown info file for the module if it does not already exist.
    '''

    #check if the header file exists in the module directory
    header_file_name = '../include/' + module_name + '/' + module_name + '.md'
    module_name_titile = module_name.replace('_', ' ').title()
    if not os.path.exists(header_file_name):
        with open(header_file_name, 'w+', encoding='utf-8') as markdown_file:
            markdown_file.write(f'# {module_name_titile}\n')
            markdown_file.write('## Problem Statement\n')
            markdown_file.write('### Example 1\n')
            markdown_file.write('### Example 2\n')
            markdown_file.write('## Solution\n')
            markdown_file.write('### Idea\n')
            markdown_file.write('### Algorithm\n')
    else:
        print('The MarkDown file already exists.')


def create_source_file(module_name):
    '''
    Creates a source file for the module if it does not already exist.
    '''

    #check if the source file exists in the source directory
    source_file_name = '../source/' + module_name + '.cpp'
    if not os.path.exists(source_file_name):
        with open(source_file_name, 'w+', encoding='utf-8') as source_file:
            source_file.write('/**\n')
            source_file.write('* @file ' + module_name + '.cpp\n')
            source_file.write('* @author Matan Levy (levymatanlevy@gmail.com)\n')
            source_file.write('* @brief\n')
            source_file.write('* @version 0.1\n')
            todays_date_string = datetime.date.today().strftime('%Y-%m-%d')
            source_file.write(f'* @date {todays_date_string}\n')
            source_file.write('*\n')
            source_file.write('*\n')
            source_file.write('*/\n')
            source_file.write('#include <' + module_name + '/' + module_name + '.h>\n')
            source_file.write('\n')
    else:
        print('The source file already exists.')

def create_test_file(module_name):
    '''
    Creates a test file for the module if it does not already exist.
    '''

    #check if the test file exists in the test/source directory
    test_file_name = '../test/source/' + module_name + '.cpp'
    if not os.path.exists(test_file_name):
        with open(test_file_name, 'w+', encoding='utf-8') as test_file:
            test_file.write('/**\n')
            test_file.write('* @file ' + module_name + '.cpp\n')
            test_file.write('* @brief\n')
            test_file.write('* @version 0.1\n')
            todays_date_string = datetime.date.today().strftime('%Y-%m-%d')
            test_file.write(f'* @date {todays_date_string}\n')
            test_file.write('*\n')
            test_file.write('*\n')
            test_file.write('*/\n')
            test_file.write('#include <doctest/doctest.h>\n')
            test_file.write('#include <' + module_name + '/' + module_name + '.h>\n')
            test_file.write('\n')
    else:
        print('The test file already exists.')


if __name__ == '__main__':

    # Make sure the user is in the tools directory
    if not os.path.exists('initialize_new_model.py'):
        print('Please run this script from the tools directory')
        sys.exit(1)

    module_name = input('Enter module name: ')
    # convert module name to lower case and seperate words by '_' instead of ' '
    module_name = module_name.lower().replace(' ', '_')

    make_directories(module_name)
    create_header_file(module_name)
    create_md_file(module_name)
    create_source_file(module_name)
    create_test_file(module_name)
