import React, { useEffect, useState } from 'react';
import axios from 'axios';

const Web = () => {
  const [slots, setSlots] = useState({});

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(
          'https://ap-southeast-1.aws.data.mongodb-api.com/app/application-0-pdtrfvc/endpoint/PostFromMongoDBtoReactJs'
        );
        setSlots(response.data);
      } catch (error) {
        console.error("Lỗi khi lấy dữ liệu từ MongoDB:", error);
      }
    };

    fetchData();
  }, []);

  // Inline styles
  const styles = {
    shelfContainer: {
      marginBottom: '30px',
      textAlign: 'center',
    },
    gridContainer3x3: {
      display: 'grid',
      gridTemplateColumns: 'repeat(3, 1fr)',
      gridTemplateRows: 'repeat(3, 1fr)',
      gap: '10px',
      width: '70vw',
      maxWidth: '400px',
      margin: 'auto',
      padding: '20px',
    },
    gridContainer3x6: {
      display: 'grid',
      gridTemplateColumns: 'repeat(6, 1fr)',
      gridTemplateRows: 'repeat(3, 1fr)',
      gap: '10px',
      width: '90vw',
      maxWidth: '800px',
      margin: 'auto',
      padding: '20px',
    },
    gridItem: {
      display: 'flex',
      justifyContent: 'center',
      alignItems: 'center',
      fontWeight: 'bold',
      color: 'white',
      height: '100px',
      borderRadius: '8px',
      fontSize: '1.2em',
      transition: 'background-color 0.3s ease',
    },
    red: {
      backgroundColor: '#e74c3c',
    },
    green: {
      backgroundColor: '#2ecc71',
    },
  };

  // Render a single shelf
  const renderShelf = (startIndex, endIndex, is3x3 = false) => (
    <div style={is3x3 ? styles.gridContainer3x3 : styles.gridContainer3x6}>
      {Array.from({ length: endIndex - startIndex + 1 }, (_, index) => {
        const slotKey = `slot_${startIndex + index}`;
        const slotValue = parseFloat(slots[slotKey]); // Parse the value as a number
        const boxStyle = slotValue === 1 ? styles.green : styles.red;

        return (
          <div key={slotKey} style={{ ...styles.gridItem, ...boxStyle }}>
            {slotKey}
          </div>
        );
      })}
    </div>
  );

  return (
    <div>
      <div style={styles.shelfContainer}>
        <h2>Shelf 1</h2>
        {renderShelf(1, 9, true)} {/* Slot 1 to Slot 9 in a 3x3 grid */}
      </div>
      <div style={styles.shelfContainer}>
        <h2>Shelf 2</h2>
        {renderShelf(10, 27)} {/* Slot 10 to Slot 27 in a 3x6 grid */}
      </div>
      <div style={styles.shelfContainer}>
        <h2>Shelf 3</h2>
        {renderShelf(28, 45)} {/* Slot 28 to Slot 45 in a 3x6 grid */}
      </div>
    </div>
  );
};

export default Web;
