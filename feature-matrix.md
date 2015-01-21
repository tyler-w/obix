# oBIX Feature matrix

The purpose of this document is to outline the implemented features inside the oBIX server in line with the [oBIX specification 1.1](https://www.oasis-open.org/committees/download.php/38212/oBIX-1-1-spec-wd06.pdf) provided by OASIS.

The document is comprised of a feature list of <x> features:

* Object Model

## Object Model

The oBIX object model describes oBIX objects that are fundamental to the machine-to-machine communication, and consist of a fixed set of object types that must be understood and implemented by the server.

**Abstract**:
Each complex type must be able to be **read**, **write**n, and sometimes **invoked** by clients.  Each type must be checked and enforced at the server to prevent misuse of the type (for example, writing a `str` to a `bool` object, and so forth).

Items prefixed with an `@` indicate the proper handling of certain valid attributes on an object, according to the oBIX data model.

**Criterion**:
Complex object items may be marked as complete only if:

* **read**: Clients **must** be able to fully read the object in its entirety from storage when requested by a client.
* **write**: Clients **must** be able to fully write the object **and any changed attribute** when requested by a client, including deleting the full extent of the object if the client requested it to be set null, **only** if `writable` is set to `true`.
* **invoke**: Clients **must** be able to invoke the `op`eration and have the oBIX server perform a function, and return the client a valid result.
* **Integrity checking**:  The server **must** check and enforce integrity, and only accept perfect input for a each type, and a valid `obix:err` contract **must** be returned if the sanity check fails. Each changed attribute and child in an object's extent must be fully checked for validity before modifying the oBIX server's object model.

## Reference Types

Reference, or "complex" types do not have a `val` attribute, and do not carry a value themselves; rather, they are mechanisms and containers that support the manipulation and categorization of value objects.

### `obix:obj`

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

### `obix:list`

`obix:list` is a collection element, and supports grouping of lists of nodes.

- [ ] Read
- [ ] Write
  - [ ] @of
  - [ ] @min
  - [ ] @max
- [ ] Integrity Checking and enforcement

### `obix:op`

`obix:op` is the operation mechanism:  It enables the oBIX server to be able to support procedures.  It should be the only node that supports the `obix:invoke` operation.

- [ ] Read
- [ ] Write
  - [ ] @in
  - [ ] @out
- [ ] Invoke
- [ ] Integrity Checking and enforcement

### `obix:ref`
`obix:ref` nodes provide an anchor mechanism to refer clients to other locations in the tree, possibly even externally.

- [ ] Read
- [ ] Write

### `obix:err`
`obix:err` contracts provide an error informing mechanism to inform clients of any errors encountered for a request it may perform.  You cannot write `obix:err` contracts to an oBIX server.

- [ ] Read

## Value types

Value types **must** have a `val` attribute, **or** be set to null with `null=true`.  Both `val` and `null` **must** not coexist on the same object.

Value types **must** not have children.

### `obix:bool`
The bool object represents a boolean condition of either true or false. Its val attribute maps to `xs:boolean` defaulting to `false`. The literal value of a bool MUST be “true” or “false” (the literals `1` and `0` are not allowed).

- [ ] Read
- [ ] Write
- [ ] `xs:boolean` integrity checking and enforcement

### `obix:int`
The `int` type represents an integer number. Its `val` attribute maps to `xs:long` as a 64-bit integer with a default of `0`.

- [ ] Read
- [ ] Write
- [ ] `xs:long` integrity checking and enforcement

### `obix:real`

The `real` type represents a floating point number. Its `val` attribute maps to `xs:double` as a IEEE 64-bit floating point number with a default of `0`.

- [ ] Read
- [ ] Write
- [ ] `xs:double` integrity checking and enforcement

### `obix:str`
The `str` type represents a string of Unicode characters. Its `val` attribute
maps to `xs:string` with a default of the empty string. 

- [ ] Read
- [ ] Write
- [ ] `xs:string` integrity checking and enforcement

### `obix:enum`
The `enum` type is used to represent a value which must match a finite set of
values. The finite value set is called the range. The `val` attribute of an 
`enum` is represented as a string key using `xs:string` Defaults to null. 
The range of an `enum` is declared via facets using the `range` attribute.

- [ ] Read
- [ ] Write
- [ ] `xs:string` integrity checking and enforcement

### `obix:abstime`
The `abstime` type is used to represent an absolute point in time. Its `val` 
attribute maps to `xs:dateTime`, with the exception that the **timezone is 
required**. Defaults to null.

- [ ] Read
- [ ] Write
- [ ] `xs:dateTime` integrity checking and enforcement

### `obix:reltime`
The `reltime` type is used to represent a relative duration of time, or a 
timespan. Its `val` attribute maps to `xs:duration` with a default of `0sec`.
- [ ] Read
- [ ] Write
- [ ] `xs:duration` integrity checking and enforcement

### `obix:date`
The date type is used to represent a day in time as a day, month, and year. 
Its `val` attribute maps to `xs:date`.

- [ ] Read
- [ ] Write
- [ ] `xs:date` integrity checking and enforcement

### `obix:time`
The `time` type is used to represent a time of day in hours, minutes, and 
seconds. Its `val` attribute maps to `xs:time`.

Time values in oBIX **MUST** omit the timezone offset and MUST NOT use the 
trailing “Z”. Only the `tz` attribute SHOULD be used to associate the time 
with a timezone. Time objects default to null.

- [ ] Read
- [ ] Write
- [ ] `xs:time` integrity checking and enforcement

### `obix:uri`
The uri type is used to store a URI reference. Unlike a plain old str, a uri 
has a restricted lexical space as defined by RFC 3986 and XML Schema `xs:anyURI` 
type.

- [ ] Read
- [ ] Write
- [ ] `xs:anyURI` integrity checking and enforcement

