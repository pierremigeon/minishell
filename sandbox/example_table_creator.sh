#!/bin/bash
echo -e "Commit_id\tFiles\tInsert\tDelete\tSum" > test; for id in $(git log --oneline | awk '{print $1}'); do echo $(git show $id --stat | tail -n1) | tr ',' '\n' | tee >(echo -ne "$id\t\t" >> test) >(grep -e '(+)' -e '(-)' | sed s/[^0-9\ ]//g | tr '\n' ' ' | awk '{print $1 + $2}' >> test) >(d=$(grep '-' | sed s/[^0-9]//g); if [[ $d ]]; then echo -ne "$d\t" >> test; else echo -ne "0\t" >> test; fi)  >(i=$(grep '(+)' | sed s/[^0-9]//g); if [[ $i ]]; then echo -ne $i "\t" >> test; else echo -ne "0\t" >> test; fi) >(grep 'changed' | sed s/[^0-9]//g | tr '\n' '\t' >> test) | cd .; done;