COPY %1\bioblocksExecution.dll X:\bioblocksExecution\dll_%2\bin\bioblocksExecution.dll
COPY %1\bioblocksExecution.lib X:\bioblocksExecution\dll_%2\bin\bioblocksExecution.lib

DEL /S X:\bioblocksExecution\dll_%2\include\*.h
XCOPY /S /Y X:\bioblocksExecution\bioblocksExecution\*.h X:\bioblocksExecution\dll_%2\include