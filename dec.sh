#!/bin/bash

# 检查参数数量是否正确
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <true|false>"
    exit 1
fi

# 获取传入的参数值
param="$1"

# 根据参数值创建相应的文件夹
if [ "$param" = "true" ]; then

    mkdir true
    echo "Created 'true' folder."
elif [ "$param" = "false" ]; then
    mkdir false
    echo "Created 'false' folder."
else
    echo "Invalid parameter. Usage: $0 <true|false>"
    exit 1
fi
