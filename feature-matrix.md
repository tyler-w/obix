# oBIX Feature matrix

The purpose of this document is to outline the implemented features inside the oBIX server in line with the [oBIX specification 1.1](https://www.oasis-open.org/committees/download.php/38212/oBIX-1-1-spec-wd06.pdf) provided by OASIS.

Items checked in this list have been implemented *in their entirety* according to the full extent of the specification.  Items in this list that have not, or partially implemented **should not** be acknowledged in this list, notwithstanding individual criterion defined for each subsection.

## Object Model (§4)

The oBIX object model describes oBIX objects that are fundamental to the machine-to-machine communication, and consist of a fixed set of object types that must be understood and implemented by the server.

**Abstract**:
Each complex type must be able to be **read**, **write**n, and sometimes **invoked** by clients.  Each type must be checked and enforced at the server to prevent misuse of the type (for example, writing a `str` to a `bool` object, and so forth).

Items prefixed with an `@` indicate the proper handling of certain valid attributes on an object, according to the oBIX data model.

**Criterion**:
Complex object items may be marked as complete only if:

* **read**: Clients **must** be able to fully read the object in its entirety from storage when requested by a client.
* **write**: Clients **must** be able to fully write the object **and any changed attribute** when requested by a client, including deleting the full extent of the object if the client requested it to be set null, **only** if `writable` is set to `true`.
* **invoke**: Clients **must** be able to invoke the `op`eration and have the oBIX server perform a function, and return the client a valid result.
* **Integrity checking**:
  * The server **must** check and enforce integrity, and only accept perfect input for a each type, and a valid `obix:err` contract **must** be returned if the sanity check fails. Each changed attribute and child in an object's extent must be fully checked for validity before modifying the oBIX server's object model.
  * Any facets listed in the data model for a data type **must** be adhered to

## Reference Types

Reference, or "complex" types do not have a `val` attribute, and do not carry a value themselves; rather, they are mechanisms and containers that support the manipulation and categorization of value objects.

#### `obix:obj` (§4.1)

`obj` is the root oBIX object.  Every type derives from `obj`.

- [ ] Read
- [ ] Write
  - [ ] @name
  - [ ] @href
  - [ ] @is
  - [ ] @null
  - [ ] @icon
  - [ ] @displayName
  - [ ] @display
  - [ ] @writable
  - [ ] @status
- [ ] Integrity Checking and enforcement

#### `obix:list` (§4.12)

`obix:list` is a collection element, and supports grouping of lists of nodes.

- [ ] Read
- [ ] Write
  - [ ] @of
  - [ ] @min
  - [ ] @max
- [ ] Integrity Checking and enforcement

#### `obix:op` (§4.15)

`obix:op` is the operation mechanism:  It enables the oBIX server to be able to support procedures.  It should be the only node that supports the `obix:invoke` operation.

- [ ] Read
- [ ] Write
  - [ ] @in
  - [ ] @out
- [ ] Invoke
- [ ] Integrity Checking and enforcement

#### `obix:ref` (§4.13)
`obix:ref` nodes provide an anchor mechanism to refer clients to other locations in the tree, possibly even externally.

- [ ] Read
- [ ] Write

#### `obix:err` (§4.14)
`obix:err` contracts provide an error informing mechanism to inform clients of any errors encountered for a request it may perform.  You cannot write `obix:err` contracts to an oBIX server.

- [ ] Read

#### `obix:feed` (§4.16)
The `feed` object is used to define a topic for a feed of events. Feeds are used with watches to subscribe
to a stream of events such as alarms. A feed SHOULD specify the event type it fires via the of attribute.
The `in` attribute can be used to pass an input argument when subscribing to the feed (a filter for example).

## Value types

Value types **must** have a `val` attribute, **or** be set to null with `null=true`.  Both `val` and `null` **must** not coexist on the same object.

#### `obix:bool` (§4.2)
The bool object represents a boolean condition of either true or false. Its val attribute maps to `xs:boolean` defaulting to `false`. The literal value of a bool MUST be “true” or “false” (the literals `1` and `0` are not allowed).

- [ ] Read
- [ ] Write
- [ ] `xs:boolean` integrity checking and enforcement

#### `obix:int` (§4.3)
The `int` type represents an integer number. Its `val` attribute maps to `xs:long` as a 64-bit integer with a default of `0`.

- [ ] Read
- [ ] Write
- [ ] `xs:long` integrity checking and enforcement

#### `obix:real` (§4.4)

The `real` type represents a floating point number. Its `val` attribute maps to `xs:double` as a IEEE 64-bit floating point number with a default of `0`.

- [ ] Read
- [ ] Write
- [ ] `xs:double` integrity checking and enforcement

#### `obix:str` (§4.5)
The `str` type represents a string of Unicode characters. Its `val` attribute
maps to `xs:string` with a default of the empty string. 

- [ ] Read
- [ ] Write
- [ ] `xs:string` integrity checking and enforcement

#### `obix:enum` (§4.6)
The `enum` type is used to represent a value which must match a finite set of
values. The finite value set is called the range. The `val` attribute of an 
`enum` is represented as a string key using `xs:string` Defaults to null. 
The range of an `enum` is declared via facets using the `range` attribute.

- [ ] Read
- [ ] Write
- [ ] `xs:string` integrity checking and enforcement

#### `obix:abstime` (§4.7)
The `abstime` type is used to represent an absolute point in time. Its `val` 
attribute maps to `xs:dateTime`, with the exception that the **timezone is 
required**. Defaults to null.

- [ ] Read
- [ ] Write
- [ ] `xs:dateTime` integrity checking and enforcement

#### `obix:reltime` (§4.8)
The `reltime` type is used to represent a relative duration of time, or a 
timespan. Its `val` attribute maps to `xs:duration` with a default of `0sec`.
- [ ] Read
- [ ] Write
- [ ] `xs:duration` integrity checking and enforcement

#### `obix:date` (§4.9)
The date type is used to represent a day in time as a day, month, and year. 
Its `val` attribute maps to `xs:date`.

- [ ] Read
- [ ] Write
- [ ] `xs:date` integrity checking and enforcement

#### `obix:time` (§4.10)
The `time` type is used to represent a time of day in hours, minutes, and 
seconds. Its `val` attribute maps to `xs:time`.

Time values in oBIX **MUST** omit the timezone offset and MUST NOT use the 
trailing “Z”. Only the `tz` attribute SHOULD be used to associate the time 
with a timezone. Time objects default to null.

- [ ] Read
- [ ] Write
- [ ] `xs:time` integrity checking and enforcement

#### `obix:uri` (§4.11)
The uri type is used to store a URI reference. Unlike a plain old str, a uri 
has a restricted lexical space as defined by RFC 3986 and XML Schema `xs:anyURI` 
type.

- [ ] Read
- [ ] Write
- [ ] `xs:anyURI` integrity checking and enforcement


## Facets (§4.18)

Facets are traits and constraints placed on an object type that depict its range of valid values that are inside of the normal XML schema definitions.  Both facets and XML schema validation **must** pass before the object's value is considered valid.  Facets are inserted onto objects via XML attributes.

**Criterion**
Facets are fully implemented for each object in the oBIX server when the server's sanity check obeys any facet (and default facet) installed on an oBIX object when accepting an `obix:write` for that object.

- [ ] displayName (§4.18.1)
  - [ ] obix:obj
  - [ ] obix:list
  - [ ] obix:op
  - [ ] obix:feed
  - [ ] obix:ref
  - [ ] obix:err
  - [ ] obix:bool
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:enum
  - [ ] obix:uri
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time
   
- [ ] display (§4.18.2)
  - [ ] obix:obj
  - [ ] obix:list
  - [ ] obix:op
  - [ ] obix:feed
  - [ ] obix:ref
  - [ ] obix:err
  - [ ] obix:bool
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:enum
  - [ ] obix:uri
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time

- [ ] icon (§4.18.3)
  - [ ] obix:obj
  - [ ] obix:list
  - [ ] obix:op
  - [ ] obix:feed
  - [ ] obix:ref
  - [ ] obix:err
  - [ ] obix:bool
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:enum
  - [ ] obix:uri
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time

- [ ] min (§4.18.4)
  - [ ] obix:list
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time

- [ ] max (§4.18.5)
  - [ ] obix:list
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time
  
- [ ] precision (§4.18.6)
  - [ ] obix:real

- [ ] range (§4.18.7)
  - [ ] obix:enum
  - [ ] obix:bool

- [ ] status (§4.18.8)
  - [ ] obix:obj
  - [ ] obix:list
  - [ ] obix:op
  - [ ] obix:feed
  - [ ] obix:ref
  - [ ] obix:err
  - [ ] obix:bool
  - [ ] obix:int
  - [ ] obix:real
  - [ ] obix:str
  - [ ] obix:enum
  - [ ] obix:uri
  - [ ] obix:abstime
  - [ ] obix:reltime
  - [ ] obix:date
  - [ ] obix:time


## oBIX Networking (§11)

**Criterion**

Each feature in this section conforms **in its entirety** to the description found in the specification document.  In the interest of conciseness, The specification's contents is not repeated here.

- [ ] Request/Response (§11.1)
- [ ] Read (§11.1.1)
- [ ] Write (§11.1.2)
- [ ] Invoke (§11.1.3)

- [ ] Errors (§11.2)
- [ ] Lobby Contract (§11.3)
- [ ] About Contract (§11.3)

#### Batch mechanism (§11.5)
- [ ] Batch Read
- [ ] Batch Write
- [ ] Batch Invoke

## Core Contract Library (§12)

The core contract library describes some fundamental objects in which the server **must** obey.  They are predefined, and available for all clients to use.

- [ ] obix:Nil (§12.1)
- [ ] obix:Range (§12.2)
- [ ] obix:Weekday (§12.3)
- [ ] obix:Month (§12.4)
- [ ] obix:Units (§12.5)

## Watches (§12)

The watch subsystem facilitates access to real-time information by informing the clients immediately of any change to a value in the oBIX server.

- [ ] Watch Service (§13.1)
- [ ] Watch Object (§13.2)
- [ ] Watch Components
 - [ ] Watch.add (§13.2.1)
 - [ ] Watch.remove (§13.2.2)
 - [ ] Watch.pollChanges (§13.2.3)
 - [ ] Watch.pollRefresh (§13.2.4)
 - [ ] Watch.lease (§13.2.5)
 - [ ] Watch.delete (§13.2.6)
- [ ] Watch Depth (§13.3)
- [ ] Feeds (§13.4)

## Points

Points are used in sensor systems to map ranges of values to set points, which trigger events.  This section is unused.

## History (§15)

History subsystem provides clients access to an oBIX Object's value over a period of time.

- [ ] History Object (§15.1)
- [ ] History Queries (§15.2)
 - [ ] History Filter (§15.2.1)
 - [ ] History QueryOut (§15.2.2)
 - [ ] History Record (§15.2.3)
- [ ] History Rollups (§15.3)
 - [ ] History RollupIn (§15.3.1)
 - [ ] History RollupOut (§15.3.2)
 - [ ] History RollupRecord (§15.3.3)
 - [ ] History Rollup Calculation (§15.3.4)
- [ ] History Feeds (§15.4)
- [ ] History Append (§15.5)
 - [ ] History AppendIn (§15.5.1)
 - [ ] History AppendOut (§15.5.2)

## Alarms (§16)

Alarms enable clients to query, watch, and acknowledge alarms.  An alarm is a condition generated by a piece of hardware that requires acknowledgement.

- [ ] Alarm States (§16.1)
 - [ ] Alarm Source (§16.1.1)
 - [ ] Stateful larms (§16.1.2)
- [ ] Alarm Contracts (§16.2)
 - [ ] Alarm Contract (§16.2.1)
 - [ ] StatefulAlarm Contract (§16.2.2)
 - [ ] AckAlarm Contract (§16.2.3)
- [ ] Alarm Subjects (§16.3)
- [ ] Alarm Feeds (§16.4)

## Security (§17)

The security specification defines how security and error handling should be implemented in the oBIX server by providing a set of guidelines on server behaviour in a security context.

- [ ] Error Handling (§17.1)
- [ ] Permission Model (§17.2)

## HTTP Binding (§18)

- [ ] HTTP Requests (§18.1)
 - [ ] Read any object with an `href` (§18.1)
 - [ ] Write any object with an `href` and `writable=true`
 - [ ] Invoke any `op` object.
- [ ] HTTP Content negotiation (§18.2)
- [ ] HTTP MIME Type (§18.3)
- [ ] HTTP Security (§18.4)
- [ ] HTTP Localization (§18.5)

## SOAP Binding (§19)

*This section is not used*

## Conformance (§20)

*This section is not implemented by OASIS*
