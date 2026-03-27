#!/bin/bash

echo "Катировка RUB/USDT"
if ./deb | grep "Доллар" && ./deb | grep "доллар" 
then
    echo ""
else
    echo "Error requests "
fi

echo "Катировка RUB/EUR"
./deb | grep "Евро"
