for i in {1,1-6,2,3,3-6}
do
  cd VM$i
  vagrant up
  cd ..
done
