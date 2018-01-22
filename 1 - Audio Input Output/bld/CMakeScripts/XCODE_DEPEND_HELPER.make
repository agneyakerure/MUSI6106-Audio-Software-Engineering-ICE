# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.MUSI6106Exec.Debug:
PostBuild.AudioFileIO.Debug: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/debug/MUSI6106Exec
PostBuild.sndlib.Debug: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/debug/MUSI6106Exec
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/debug/MUSI6106Exec:\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libAudioFileIO.a\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libsndlib.a
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/debug/MUSI6106Exec


PostBuild.AudioFileIO.Debug:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libAudioFileIO.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libAudioFileIO.a


PostBuild.sndlib.Debug:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libsndlib.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libsndlib.a


PostBuild.MUSI6106Exec.Release:
PostBuild.AudioFileIO.Release: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/release/MUSI6106Exec
PostBuild.sndlib.Release: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/release/MUSI6106Exec
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/release/MUSI6106Exec:\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libAudioFileIO.a\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libsndlib.a
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/release/MUSI6106Exec


PostBuild.AudioFileIO.Release:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libAudioFileIO.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libAudioFileIO.a


PostBuild.sndlib.Release:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libsndlib.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libsndlib.a


PostBuild.MUSI6106Exec.MinSizeRel:
PostBuild.AudioFileIO.MinSizeRel: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/MinSizeRel/MUSI6106Exec
PostBuild.sndlib.MinSizeRel: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/MinSizeRel/MUSI6106Exec
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/MinSizeRel/MUSI6106Exec:\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libAudioFileIO.a\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libsndlib.a
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/MinSizeRel/MUSI6106Exec


PostBuild.AudioFileIO.MinSizeRel:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libAudioFileIO.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libAudioFileIO.a


PostBuild.sndlib.MinSizeRel:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libsndlib.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libsndlib.a


PostBuild.MUSI6106Exec.RelWithDebInfo:
PostBuild.AudioFileIO.RelWithDebInfo: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/relwithdebinfo/MUSI6106Exec
PostBuild.sndlib.RelWithDebInfo: /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/relwithdebinfo/MUSI6106Exec
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/relwithdebinfo/MUSI6106Exec:\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libAudioFileIO.a\
	/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libsndlib.a
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/bin/relwithdebinfo/MUSI6106Exec


PostBuild.AudioFileIO.RelWithDebInfo:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libAudioFileIO.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libAudioFileIO.a


PostBuild.sndlib.RelWithDebInfo:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libsndlib.a:
	/bin/rm -f /Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libsndlib.a




# For each target create a dummy ruleso the target does not have to exist
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libAudioFileIO.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/MinSizeRel/libsndlib.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libAudioFileIO.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/debug/libsndlib.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libAudioFileIO.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/release/libsndlib.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libAudioFileIO.a:
/Users/agneyakerure/Desktop/Audio\ Software\ Engineering/MUSI6106-Audio-Software-Engineering-ICE/1\ -\ Audio\ Input\ Output/2018-MUSI6106-master/lib/relwithdebinfo/libsndlib.a:
