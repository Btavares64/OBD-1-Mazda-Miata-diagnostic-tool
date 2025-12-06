:- use_module(library(csv)).

% Needed for read_line_to_string
:- use_module(library(readutil)). 

% path for the log file
log_file_path('build/log.txt'). 


main :-
    log_file_path(FilePath),
    
    % 1. check if the log file exists
    (   exists_file(FilePath)
    ->  
        writeln('--- STARTING MAZDA MIATA (NA) DIAGNOSTICS ---'),
        nl,
        
        read_and_diagnose_raw(FilePath),

        nl,
        writeln('--- END OF REPORT ---')
    ;   writeln('Error: log file not found at build/log.txt.')
    ).

% for code parsing (Finds ##CODE_START## in the log.txt file) ---

read_and_diagnose_raw(FilePath) :-
    (   catch(open(FilePath, read, Stream), _, fail)
    ->  
        writeln('--- DETECTED RAW CODES (from log.txt) ---'),
        nl,
        
        (   skip_until_marker(Stream, '##CODE_START##')
        ->  % If marker is found, read and process the codes
            read_raw_codes(Stream)

        ;   writeln('Note: Raw code start marker (##CODE_START##) not found in log.txt.')
        ),

        close(Stream)
    ;   
        format('Error: Could not open log file at ~w for raw parsing.~n', [FilePath])
    ).

read_raw_codes(Stream) :-
    read_line_to_string(Stream, Line),
    (   Line == end_of_file -> 
        writeln('Warning: End marker not found in raw log file.')
    ;   sub_string(Line, _, _, _, '##CODE_END##') -> 
        true % Found end marker, terminate recursion
    ;   
        % Process the line (e.g., "10, 200")
        (   parse_raw_code(Line, Code, System)
        ->  (   suggestion(Code, System, Advice)
            ->  format('RAW CODE ~w (System ~w): ~w~n', [Code, System, Advice])
            ;   format('RAW CODE ~w (System ~w): Consult FSM (unknown raw code).~n', [Code, System])
            )
        ;   true % Skip irrelevant lines (like "Codes stored in array:")
        ),
        read_raw_codes(Stream) % Continue reading the next line
    ).

skip_until_marker(Stream, Marker) :-
    repeat,
    read_line_to_string(Stream, Line),
    (   Line == end_of_file -> 
        writeln('Warning: Start marker not found in log file.'),
        !, fail 
    ;   sub_string(Line, _, _, _, Marker) -> 
        ! 
    ;   true % Keep failing/repeating until the line is found or EOF
    ).

% parses a raw code 
parse_raw_code(String, Code, System) :-
    % Use split_string to handle the comma and whitespace
    split_string(String, ',', ' \n\r\t', Parts), 
    
    % Ensure exactly two parts were found
    length(Parts, 2),
    
    % Convert strings (which are atoms after split_string) to numbers
    maplist(atom_number, Parts, [Code, System]).

read_and_diagnose_csv(FilePath) :-
    csv_read_file(FilePath, Rows, [strip(true)]),
    writeln('--- DETECTED CSV CODES (from log.txt) ---'),
    nl,
    maplist(provide_advice, Rows).

% suggestions for the ecu

% Ignition & Timing (Codes 1, 2, 3)
suggestion(Code, 100, 'Check the Crank Angle Sensor (CAS) o-ring for leaks, inspect the 4-pin connector on the coil pack/igniter, and verify timing belt alignment.') :-
    member(Code, [1, 2, 3]).

% Airflow (Codes 8, 10)
suggestion(Code, 100, 'Inspect the Air Flow Meter (AFM) plug for corrosion. Ensure the mechanical flapper door inside the AFM moves freely and is not binding.') :-
    member(Code, [8, 10]).

% Cooling (Code 9)
suggestion(9, 100, 'Check the green coolant thermistor on the back of the engine block (under the coil pack). The wiring here is prone to breaking due to heat.').

% TPS (Code 12)
suggestion(12, 100, 'Test the Throttle Position Sensor (TPS). On a 1992, this is a switch type. Ensure it clicks when the throttle opens slightly.').

% Atmosphere (Code 14)
suggestion(14, 100, 'Check the small vacuum line running to the PA (Pressure) sensor inside the cabin (usually near the ECU footwell).').

% Oxygen Sensor (Codes 15, 17)
suggestion(Code, 100, 'The ECU is not seeing the expected voltage swing. Check for exhaust leaks before the sensor, or replace the O2 sensor.') :-
    member(Code, [15, 17]).

% Evap (Code 26)
suggestion(26, 100, 'Inspect the charcoal canister vacuum lines. Test the solenoid resistance to ensure the purge valve is not stuck open.').

% Idle (Code 34)
suggestion(34, 100, 'Idle Speed Control (ISC) valve issue. Remove the throttle body and clean the ISC valve passages with carb cleaner.').


% suggestions for the airbag module

% Internal Faults (Codes 10, 101)
suggestion(Code, 200, 'CRITICAL: Disconnect battery for 10 mins. The Blue Diagnostic Module internal thermal fuse or capacitors may have failed.') :-
    member(Code, [10, 101]).

% Power & Ground (Codes 2, 3, 7, 8)
suggestion(Code, 200, 'CRITICAL: Disconnect battery for 10 mins. Clean the ground points on the chassis (fender walls) and check the AIR BAG fuse.') :-
    member(Code, [2, 3, 7, 8]).

% Impact Sensors (Codes 4, 5, 9)
suggestion(Code, 200, 'CRITICAL: Disconnect battery for 10 mins. Inspect the front crash sensors (near hood latch) for green corrosion on the terminals.') :-
    member(Code, [4, 5, 9]).

% Clockspring (Code 6)
suggestion(6, 200, 'CRITICAL: Disconnect battery for 10 mins. The clockspring (spiral cable) behind the steering wheel has likely snapped. Horn may also not work.').