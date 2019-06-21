# Simple DBMS                                                                                                   

This project is a simple DBMS implemented using C, as the education material of the Introduction to Database Systems in National Chiao Tung University

## Prerequisite

* make >= 4.1
* gcc >= 5.4.0
* g++ >= 5.4.0
* gtest >= 1.8.1
* python >= 3.6.0

## Unit test

`$ make check`

## System test

`$ python3 test/system/system_test.py ./shell [test_case..]`

> if no test_cases is specified, it will run all system tests by default

## Compile

`$ make`

## Quick Start
`$ ./shell`

## Query

***The current table schema is hard coded, the schema in the [include/User.h](include/User.h), you can check the User_t to get the detail of each field.***

### Table schema
#### `User` table
| field_name | data_type |
|---|---|
| id | int |
| name | char[255] |
| email | char[255] |
| age | int |

### Supported command
| Command | Description |
|---|---| 
| insert | The insert command only allow insert one `User_t` record at a time |
| select | The select command will only print out all the `User_t` records in the current databases |


## Storage mode

### Memory only

The memory only will not store any record after the process terminate

#### Usage:
`$ ./shell`

### File mode

The File mode will store the record into the specify \<DB file\>, the
next execute can automatically reload the record by the same
execution command.

#### Usage:
`$ ./shell <DB file>`

## Project Layout
    ├─ include/           Header files
    ├─ src/               Source files
    │  ├─ shell.c         Entry point, which contains main()
    │  ├─ Util.c          Some utility functions
    │  ├─ Table.c
    │  ├─ SelectState.c   
    │  ├─ User.c
    │  ├─ Like.c
    │  ├─ Util.c
    │  ├─
    ├─ test/              Unit tests & system tests
    │  ├─ include/        Test header files
    │  ├─ system/         System tests
    │  └─ *.c             Unit tests source file
    └─ Makefile           Makefile for make


## Done 
1. update user set (SelectState.c - update_state_handler)
2. delete from user (SelectState.c - delete_state_handler)
3. archive table (Table.c - archive_like_table / archive_user_table)

## On doing
1. load table (Table.c - load_like_table / load_user_table)
2. 


## Todo
1. 
