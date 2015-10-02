#!/bin/bash

#printf "Host: "
#read host

host="Luke"

rsync -arvzSH --include="*.cpp" --include="*.hpp" --include="SConstruct" --include="*.lua" --include="*.sh" --include="*/" --exclude="*" ~/Projects/test/ cognizance@$host:~/Projects/test/ && ssh cognizance@$host "cd Projects/test/; scons"

scp -q cognizance@Luke:~/Projects/test/build_status ~/Projects/test/
status=$(</home/cognizance/Projects/test/build_status)

if [[ "$status" -eq 0 ]]; then
	printf "Retrieving the executable from Luke and running.\n"
	scp cognizance@Luke:~/Projects/test/No-Motivation ~/Projects/test/
	__GL_SYNC_TO_VBLANK=0 optirun ./No-Motivation
fi

