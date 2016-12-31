function make-symlinks
	set cwd (pwd)
	cd $argv[1]
	mkdir -p (python -c "print('../'*$argv[2])")shared_server/$argv[3]
	mkdir -p (python -c "print('../'*$argv[2])")shared_client/$argv[3]
	echo make-symlinks[$argv[2]]: Entering directory $cwd/$argv[1]
	for file in (ls | grep .cpp)
		echo creating symlink (python -c "print('../'*$argv[2])")shared_server/$argv[3]/$file '->' (python -c "print('../'*$argv[2])")shared/$argv[3]/$file
		ln -s -f (python -c "print('../'*$argv[2])")shared/$argv[3]/$file (python -c "print('../'*$argv[2])")shared_server/$argv[3]/$file
		echo creating symlink (python -c "print('../'*$argv[2])")shared_client/$argv[3]/$file '->' (python -c "print('../'*$argv[2])")shared/$argv[3]/$file
		ln -s -f (python -c "print('../'*$argv[2])")shared/$argv[3]/$file (python -c "print('../'*$argv[2])")shared_client/$argv[3]/$file
	end
	for dir in (ls)
		if test -d $dir
			set depth $argv[2] + 1
			make-symlinks $dir $depth $argv[3]/$dir
		end
	end
	cd $cwd
	echo make-symlinks[$argv[2]]: Leaving directory $cwd/$argv[1]
end
