#!/bin/sh
date > launch_all_results
php generateCustomTest.php < launch_all_arguments >> launch_all_results
date >> launch_all_results

