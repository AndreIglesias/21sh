#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    track.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoursou <asoursou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/09 01:10:17 by asoursou          #+#    #+#              #
#    Updated: 2021/07/31 21:10:40 by user             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

usage='\033cPress Ctrl+C to quit'
echo -e "$usage"
while true; do
	pids=`pgrep 21sh`
	if [ ! -z "$pids" ]; then
		echo -e "$usage"
		for pid in $pids; do
			echo "21sh ($pid): `lsof -p $pid | wc -l`"
			childs=`pgrep -P $pid`
			if [ -z "$childs" ]; then
				echo '  No childs process.'
			else
				echo '  Childs process:'
				for child in $childs; do
					name=`ps -p $child | tail -n 1 | cut -d ' ' -f 7`
					echo "    $name ($child): `lsof -p $child | wc -l`"
				done
			fi
		done
	fi
	sleep 2
done
