for file in `ls *.tpp`; do
  mv ./${file%} ./${file%.tpp}.hpp
done
